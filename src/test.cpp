#include <iostream>
#include "grid.h"
#include "game.h"

static void
two_player_game() {
    Game g;
    char col;
    int line;

    while (not g.IsFinished()) {
        cout << g << g.GetPlayer() << "'s turn: ";
        if (!(cin >> col >> line))
            return;
        g.Play(line - 1, col - 'a', g.GetPlayer());
    }
    cout << g;
}

int
main() {
    two_player_game();

    return 0;
}

/* vim: set ts=8 sts=4 sw=4 et : */
