#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <wx/wx.h>
#include "game.hpp"
#include "grid.hpp"
#include "computer.hpp"

// Menu IDs
enum {
    id_two_player,
    id_computer
};

class Window: public wxFrame {
private:
    wxMenuBar *_menu_bar;
    wxMenu *_game_menu;
    wxMenu *_new_submenu;
    Game *_game;
    Computer *_computer;
    wxStaticText *_score;
    struct Move _last_move;
    int _grid_size;
    bool _with_computer,
         _finished;

public:
    // Constructors
    Window();

    // Event callbacks
    void OnExit(wxCommandEvent &event);
    void OnNewGame(wxCommandEvent &event);
    void OnNewComputerGame(wxCommandEvent &event);
    void OnPaint(wxPaintEvent &event);
    void OnClick(wxMouseEvent &event);

    // Methods
    void GetWindowInfo(
        int &window_w, int &window_h,
        int &x_offset, int &y_offset,
        int &cell_size
    );

    DECLARE_EVENT_TABLE()
};

#endif /* _WINDOW_H_ */

/* vim: set ts=8 sts=4 sw=4 et : */
