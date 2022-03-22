#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "game.hpp"

#define MAX_REC 3

class Computer {
private:
    Cell _color;
public:
    Computer(Cell color): _color(color) {};
    Move GetBestMove(Game g) const;
    int MinMaxAB(
        Game g, Move move, int depth, int alpha, int beta
    ) const;
};

#endif /* _COMPUTER_H_ */

/* vim: set ts=8 sts=4 sw=4 et : */
