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

public:
    Window();
    void OnExit(wxCommandEvent &event);
    void OnPaint(wxPaintEvent &event);
    void OnClick(wxMouseEvent &event);
    void OnDraw();

    DECLARE_EVENT_TABLE()
};

#endif /* _WINDOW_H_ */

/* vim: set ts=8 sts=4 sw=4 et : */
