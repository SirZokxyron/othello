#ifndef _GAME_H_
#define _GAME_H_

#include "grid.h"
#include <cassert>

class Game {
private:
    Grid _grid;
    Cell _current_player = Black;

public:
    bool Play(int i, int j, Cell current);
    bool Visit(int i, int j, Cell current, bool test);
    bool IsValid(int i, int j, Cell current);
    bool VisitWorker(
        int i, int j, int di, int dj, const Cell &current, bool test, int count
    );
    bool IsFinished();
    void Print() const { _grid.Print(); };
    Cell GetPlayer() const { return _current_player; };
    friend ostream& operator<<(ostream& os, const Game& g);
};

#endif /* _GAME_H_ */

/* vim: set ts=8 sts=4 sw=4 et : */