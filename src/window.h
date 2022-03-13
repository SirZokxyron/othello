#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <wx/wx.h>
#include "game.h"
#include "grid.h"

class Window: public wxFrame {
private:
    wxMenuBar *_menu_bar;
    wxMenu *_game_menu;
    Game *_game;
    wxStaticText *_current_player,
                 *_score_white,
                 *_score_black;
    int _grid_size;

public:
    // Constructors
    Window();

    // Event callbacks
    void OnExit(wxCommandEvent &event);
    void OnNewGame(wxCommandEvent &event);
    void OnPaint(wxPaintEvent &event);
    void OnClick(wxMouseEvent &event);

    // Methods
    void OnDraw();
    void GetWindowInfo(
        int &window_w, int &window_h,
        int &x_offset, int &y_offset,
        int &cell_size
    );

    DECLARE_EVENT_TABLE()
};

#endif /* _WINDOW_H_ */

/* vim: set ts=8 sts=4 sw=4 et : */
