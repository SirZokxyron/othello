#include "window.h"

Window::Window(): wxFrame(NULL, wxID_ANY, "Othello", wxDefaultPosition, wxSize(500, 500)) {
    // Game attributes
    _grid_size = 8;

    // Game menu
    _game_menu = new wxMenu();
    _game_menu->Append(wxID_NEW, wxT("&New"));
    _game_menu->Append(wxID_EXIT, wxT("&Quit"));

    // Menu bar
    _menu_bar = new wxMenuBar();
    _menu_bar->Append(_game_menu, "&Game");
    SetMenuBar(_menu_bar);

    // Texts
    _score_white = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition);
    _score_black = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition);
    _current_player = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition);
    _current_player->SetOwnBackgroundColour(wxColour("#b3d9ff"));
    _current_player->SetForegroundColour("Black");

    // Shorcuts
    wxAcceleratorEntry entries[2];
    entries[0].Set(wxACCEL_CTRL, 'N', wxID_NEW);
    entries[1].Set(wxACCEL_CTRL, 'X', wxID_EXIT);
    wxAcceleratorTable accel(2, entries);
    SetAcceleratorTable(accel);

    // Game init
    _game = new Game;
}

void Window::OnExit(wxCommandEvent &event) {
    event.Skip();
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

void Window::OnDraw() {
    wxClientDC dc(static_cast<wxWindow *>(this));
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
            case Black:
                dc.SetBrush(*wxBLACK_BRUSH);
                break;

            case White:
                dc.SetBrush(*wxWHITE_BRUSH);
                break;

            default:
                continue;
            }
            dc.DrawCircle(
                i*cell_size + cell_size/2 + x_offset,
                j*cell_size + cell_size/2 + y_offset,
                cell_size/3
            );
        }
    }

    // Draw the score

    // White on the left
    {
        wxCoord text_h, text_w;
        const char *white_msg = " White's turn ",
                   *black_msg = " Black's turn ",
                   *current_player_msg;
        // TODO update score to real values

        // White on the left
        dc.SetBrush(*wxWHITE_BRUSH);
        dc.DrawCircle(cell_size + x_offset, cell_size, cell_size/3);
        dc.GetMultiLineTextExtent(wxT("2"), &text_w, &text_h);
        _score_white->Move(2*cell_size + x_offset, cell_size - text_h/2);
        _score_white->SetLabel(wxT("2"));

        // Black on the right
        dc.SetBrush(*wxBLACK_BRUSH);
        dc.DrawCircle(window_w - x_offset - cell_size, cell_size, cell_size/3);
        dc.GetMultiLineTextExtent(wxT("2"), &text_w, &text_h);
        _score_black->Move(
            window_w - x_offset - 2*cell_size - text_w,
            cell_size - text_h/2
        );
        _score_black->SetLabel(wxT("2"));

        // Current player
        current_player_msg = (_game->GetPlayer() == Black ? black_msg : white_msg);
        dc.GetMultiLineTextExtent(wxString(current_player_msg), &text_w, &text_h);
        _current_player->SetLabel(wxString(current_player_msg));
        _current_player->Move((window_w - text_w)/2, cell_size - text_h/2);
    }
}

void Window::OnPaint(wxPaintEvent &event) {
    OnDraw();
    event.Skip();
}

void Window::OnClick(wxMouseEvent &event) {
    wxCoord window_w, window_h,
            cell_size,
            x_offset, y_offset,
            x, y,
            i, j;

    // Window info
    GetWindowInfo(window_w, window_h, x_offset, y_offset, cell_size);

    // Cursor position
    x = event.GetX();
    y = event.GetY();

    // Cell index
    i = (x - x_offset)/cell_size;
    j = (y - y_offset)/cell_size;

    // Was the click in the board?
    if (0 <= i and i < _grid_size and 0 <= j and j < _grid_size) {
        _game->Play(i, j, _game->GetPlayer());
        OnDraw();
    }

    event.Skip();
}

void Window::OnNewGame(wxCommandEvent &event) {
    // Free old game
    delete _game;

    // New game
    _game = new Game;
    OnDraw();

    event.Skip();
}

BEGIN_EVENT_TABLE(Window, wxFrame)
    EVT_MENU(wxID_EXIT, Window::OnExit)
    EVT_MENU(wxID_NEW, Window::OnNewGame)
    EVT_PAINT(Window::OnPaint)
    EVT_LEFT_DOWN(Window::OnClick)
END_EVENT_TABLE()

/* vim: set ts=8 sts=4 sw=4 et : */
