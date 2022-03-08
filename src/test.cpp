#include <iostream>
#include "grid.h"
#include "game.h"

int
main() {
    Game g;

    g.Print();
    g.Play(2, 3, Black);
    g.Print();

    return 0;
}

/* vim: set ts=8 sts=4 sw=4 et : */
