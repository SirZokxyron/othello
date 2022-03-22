#include <iostream>
#include "../src/grid.hpp"
#include "../src/game.hpp"

static void
two_player_game() {
    Game g;
    char col;
    int line;

    while (not g.IsFinished()) {
        cout << g << g.GetPlayer() << "'s turn: ";
        if (!(cin >> col >> line))
            return;
        g.Play(Move(line - 1, col - 'a'), g.GetPlayer());
        // ANSI esc code to go up 1 line, erase it, then go up 12 lines at the beginning
        cout << "\x1b[1A\x1b[2K\x1b[12F";
    }
    cout << g;
}

int
main() {
    two_player_game();

    return 0;
}

/* vim: set ts=8 sts=4 sw=4 et : */
