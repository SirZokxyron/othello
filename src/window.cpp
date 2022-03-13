#include "window.h"

Window::Window(): wxFrame(NULL, wxID_ANY, "Othello", wxDefaultPosition, wxSize(500, 500)) {
    // Green background
    SetBackgroundColour("GREEN");
    // Game menu
    _game_menu = new wxMenu();
    _game_menu->Append(wxID_EXIT, _T("&Quit"));

    // Menu bar
    _menu_bar = new wxMenuBar();
    _menu_bar->Append(_game_menu, "&Game");
    SetMenuBar(_menu_bar);

    // Game init
    _game = new Game;
}

void Window::OnExit(wxCommandEvent &event) {
    Destroy();

    event.Skip();
}

void Window::OnDraw() {
    wxClientDC dc(static_cast<wxWindow *>(this));
    int window_w, window_h;
    wxCoord cell_width, cell_height;

    // size of the current window
    Window::GetSize(&window_w, &window_h);
    window_h -= _menu_bar->GetSize().GetHeight();

    // size of single tile
    cell_width = window_w / 8;
    cell_height = window_h / (8 + 1);

    // draw grid
    dc.SetBrush(*wxBLACK_BRUSH);
    for (int i = 1; i <= 8; ++i) {
        if (i != 8)
            dc.DrawLine(i*cell_width, cell_height, i*cell_width, window_h);
        dc.DrawLine(0, i*cell_height, window_w, i*cell_height);
    }

    // draw dots
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
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
                i*cell_width + cell_width/2, (j + 1)*cell_height + cell_height/2,
                min(cell_height, cell_height)/3
            );
        }
    }
}

void Window::OnPaint(wxPaintEvent &event) {
    OnDraw();
    event.Skip();
}

void Window::OnClick(wxMouseEvent &event) {
    wxCoord x, y, cell_width, cell_height;
    int window_w, window_h, i, j;

    // size of the current window
    Window::GetSize(&window_w, &window_h);
    window_h -= _menu_bar->GetSize().GetHeight();

    cell_width = window_w / 8;
    cell_height = window_h / (8 + 1);

    x = event.GetX();
    y = event.GetY();

    i = x/cell_width;
    j = y/cell_height - 1;

    _game->Play(i, j, _game->GetPlayer());
    OnDraw();

    event.Skip();
}

BEGIN_EVENT_TABLE(Window, wxFrame)
    EVT_MENU(wxID_EXIT, Window::OnExit)
    EVT_PAINT(Window::OnPaint)
    EVT_LEFT_DOWN(Window::OnClick)
END_EVENT_TABLE()

/* vim: set ts=8 sts=4 sw=4 et : */
