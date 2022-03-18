#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "game.hpp"

#define MAX_REC 6

struct Move {
	int _i;
	int _j;
	Move(int i, int j): _i(i), _j(j) {};
	friend ostream& operator<<(ostream& _os, Move& m);
};

class Computer {
private:
	Cell _color;
public:
	Computer(Cell color): _color(color) {};
	Move GetBestMove(Game g) const;
	int MinMaxAB(Game g, int i, int j, int depth, int alpha, int beta, Cell current) const;
};

#endif /* _COMPUTER_H_ */

/* vim: set ts=8 sts=4 sw=4 et : */