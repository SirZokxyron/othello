#include "window.hpp"

Window::Window(): wxFrame(NULL, wxID_ANY, "Othello", wxDefaultPosition, wxSize(500, 500)) {
    // Game attributes
    _grid_size = 8;
    _with_computer = false;
    _finished = false;
    _computer = nullptr;
    _last_move.i = _last_move.j = -1;

    // New computer game subsubmenu
    _new_computer_subsubmenu = new wxMenu();
    _new_computer_subsubmenu->Append(id_computer_black, wxT("&Black as computer"));
    _new_computer_subsubmenu->Append(id_computer_white, wxT("&White as computer"));

    // New submenu
    _new_submenu = new wxMenu();
    _new_submenu->Append(id_two_player, wxT("&Two player"));
    _new_submenu->Append(wxID_ANY, wxT("&Against computer"), _new_computer_subsubmenu);

    // Game menu
    _game_menu = new wxMenu();
    _game_menu->Append(wxID_ANY, wxT("&New"), _new_submenu);
    _game_menu->Append(wxID_EXIT, wxT("&Quit"));

    // Menu bar
    _menu_bar = new wxMenuBar();
    _menu_bar->Append(_game_menu, wxT("&Game"));
    SetMenuBar(_menu_bar);

    // Texts
    _score = new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);

    // Shorcuts
    wxAcceleratorEntry entries[2];
    entries[0].Set(wxACCEL_CTRL, 'N', id_two_player);
    entries[1].Set(wxACCEL_CTRL, 'Q', wxID_EXIT);
    wxAcceleratorTable accel(2, entries);
    SetAcceleratorTable(accel);

    // Game init
    _game = new Game;
}

void Window::OnExit(wxCommandEvent &event) {
    event.Skip();

    // Delete the window
    Destroy();
}

void Window::GetWindowInfo(
    int &window_w, int &window_h,
    int &x_offset, int &y_offset,
    int &cell_size
) {
    // Size of the current window
    Window::GetSize(&window_w, &window_h);
    window_h -= _menu_bar->GetSize().GetHeight();

    // Size of single tile
    cell_size = min(window_w/_grid_size, window_h/(_grid_size + 3));

    // Padding
    x_offset = (window_w - cell_size*_grid_size)/2;
    y_offset = 2*cell_size;
}

void Window::OnPaint(wxPaintEvent &event) {
    wxPaintDC dc(this);
    wxCoord window_w, window_h,
            cell_size,
            x_offset, y_offset;

    // Window info
    GetWindowInfo(window_w, window_h, x_offset, y_offset, cell_size);

    // Draw the grid: We slide a square to draw the grid
    wxRect square(wxSize(cell_size, cell_size));
    square.Offset(0, y_offset);
    dc.SetBrush(wxColour("Green"));
    for (int i = 0; i < _grid_size; ++i) {
        square.SetLeft(x_offset);
        for (int j = 0; j < _grid_size; ++j) {
            dc.DrawRectangle(square);
            square.Offset(cell_size, 0);
        }
        square.Offset(0, cell_size);
    }

    // Draw dots
    for (int i = 0; i < _grid_size; ++i) {
        for (int j = 0; j < _grid_size; ++j) {
            switch(_game->GetCell(i, j)) {
            case Black: // Black dots
                dc.SetBrush(*wxBLACK_BRUSH);
                break;

            case White: // White dots
                dc.SetBrush(*wxWHITE_BRUSH);
                break;

            default:    // Empty cell
                continue;
            }
            dc.DrawCircle(
                j*cell_size + cell_size/2 + x_offset,
                i*cell_size + cell_size/2 + y_offset,
                cell_size/3
            );
        }
    }

    // Draw the score
    // The current player has its stone padded in red
    {
        wxCoord text_h, text_w;
        wxString score_string;

        // Create a string containing the score
        score_string = wxString::Format(
            "%d - %d", _game->GetScore(White), _game->GetScore(Black)
        );

        // Moving the score: Maybe use a sizer?
        _score->SetLabel(score_string);
        dc.GetMultiLineTextExtent(score_string, &text_w, &text_h);
        _score->Move(window_w/2 - text_w/2, cell_size - text_h/2);

        // Draw a white on stone
        if (_game->GetPlayer() == White)
            dc.SetPen(wxPen(*wxRED, 2, wxSOLID));
        else
            dc.SetPen(*wxBLACK_PEN);
        dc.SetBrush(*wxWHITE_BRUSH);
        dc.DrawCircle(window_w/2 - text_w/2 - cell_size, cell_size, cell_size/3);

        // Draw a black stone
        if (_game->GetPlayer() == Black)
            dc.SetPen(wxPen(*wxRED, 2, wxSOLID));
        else
            dc.SetPen(*wxBLACK_PEN);
        dc.SetBrush(*wxBLACK_BRUSH);
        dc.DrawCircle(window_w/2 + text_w/2 + cell_size, cell_size, cell_size/3);
    }

    // Draw the last move
    if (_last_move.i >= 0 and _last_move.j >= 0) {
        dc.SetPen(*wxYELLOW_PEN);
        dc.SetBrush(*wxRED_BRUSH);
        dc.DrawCircle(
            _last_move.j*cell_size + cell_size/2 + x_offset,
            _last_move.i*cell_size + cell_size/2 + y_offset,
            5
        );
    }
}

void Window::OnClick(wxMouseEvent &event) {
    wxCoord window_w, window_h,
            cell_size,
            x_offset, y_offset,
            x, y,
            i, j;

    // If finished we do nothing
    if (_finished) {
        event.Skip();
        return;
    }

    // Window info
    GetWindowInfo(window_w, window_h, x_offset, y_offset, cell_size);

    // Cursor position
    x = event.GetX();
    y = event.GetY();

    // Cell index
    i = (y - y_offset)/cell_size;
    j = (x - x_offset)/cell_size;

    // Creation of a move
    // We have to use the struct keyword because of the method this->Move();
    struct Move move(i, j);

    // Was the click in the board?
    if (0 <= i and i < _grid_size and 0 <= j and j < _grid_size) {
        // Play the move, and save it
        if (_game->Play(move, _game->GetPlayer()))
            _last_move = move;

        // Let the computer play while it is its turn
        // We use a while loop in case the other player passes his turn
        if (_with_computer)
            while (_game->GetPlayer() == _computer->GetColor() and not _game->IsFinished()) {
                _last_move = _computer->GetBestMove(*_game);
                _game->Play(_last_move, _game->GetPlayer());
            }

        // Draw the grid
        Refresh();
    }

    // End of game popup message
    if (_game->IsFinished()) {
        int score_black = _game->GetScore(Black),
            score_white = _game->GetScore(White);
        wxString win_message;

        // Setting the finish state
        _finished = true;

        // Setting the win message
        if (score_black == score_white) {
            // Draw
            win_message = wxString("Draw match !");
        } else if (score_black < score_white) {
            // White wins
            win_message = wxString("White wins the match !");
        } else {
            // Black wins
            win_message = wxString("Black wins the match !");
        }

        // Popping a dialog
        wxMessageDialog *dial = new wxMessageDialog(
            NULL, win_message, wxT("End"), wxOK
        );
        dial->ShowModal();
    }

    event.Skip();
}

void Window::OnNewGame(wxCommandEvent &event) {
    // Free old game
    delete _game;

    // Free old computer if exists
    if (_computer != nullptr)
        delete _computer;

    // New game
    _game = new Game;
    _with_computer = false;
    _computer = nullptr;

    // Reset states
    _finished = false;
    _last_move.i = _last_move.j = -1;

    // Draw the grid
    Refresh();

    event.Skip();
}

void Window::OnNewComputerGame(wxCommandEvent &event) {
    // Free old game
    delete _game;

    // Free old computer if exists
    if (_computer != nullptr)
        delete _computer;

    // New game with computer
    _game = new Game;
    _with_computer = true;
    if (event.GetId() == id_computer_black) {
        // The computer has to play first
        _computer = new Computer(Black);
        _last_move = _computer->GetBestMove(*_game);
        _game->Play(_last_move, _game->GetPlayer());
    } else {
        _computer = new Computer(White);
    }

    // Reset states
    _finished = false;
    _last_move.i = _last_move.j = -1;

    // Draw the grid
    Refresh();

    event.Skip();
}

BEGIN_EVENT_TABLE(Window, wxFrame)
    EVT_MENU(wxID_EXIT, Window::OnExit)
    EVT_MENU(id_computer_black, Window::OnNewComputerGame)
    EVT_MENU(id_computer_white, Window::OnNewComputerGame)
    EVT_MENU(id_two_player, Window::OnNewGame)
    EVT_PAINT(Window::OnPaint)
    EVT_LEFT_DOWN(Window::OnClick)
END_EVENT_TABLE()

/* vim: set ts=8 sts=4 sw=4 et : */
