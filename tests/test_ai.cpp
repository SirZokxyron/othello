#include <iostream>
#include "../src/grid.hpp"
#include "../src/game.hpp"
#include "../src/computer.hpp"
#include <unistd.h>

static void
two_player_game() {
    Game g;

    Computer B(Black);
    Computer W(White);
    Move move(0, 0);

    while (not g.IsFinished()) {
        cout << g << g.GetPlayer() << "'s turn: ";
        if (g.GetPlayer() == Black)
            move = B.GetBestMove(g);
        else
            move = W.GetBestMove(g);
        g.Play(move._i, move._j, g.GetPlayer());
        // ANSI esc code to go up 1 line, erase it, then go up 12 lines at the beginning
        cout << move._i << " "  << move._j << endl;
        cout << "\x1b[1A\x1b[2K\x1b[12F";
        // sleep(1);
    }
    cout << g;
}

int
main() {
    two_player_game();

    return 0;
}

/* vim: set ts=8 sts=4 sw=4 et : */
