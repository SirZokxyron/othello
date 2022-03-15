#include "othello.h"

bool Othello::OnInit() {
    Window *window;

    window = new Window();
    window->Show();

    return true;
}

IMPLEMENT_APP(Othello)

/* vim: set ts=8 sts=4 sw=4 et : */
