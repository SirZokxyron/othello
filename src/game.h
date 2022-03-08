#ifndef _GAME_H_
#define _GAME_H_

#include "grid.h"
#include <cassert>

class Game {
private:
    Grid _grid;

public:
    bool Play(int i, int j, Cell current);
    bool Visit(int i, int j, int di, int dj, const Cell &current);
    void Print() const { _grid.Print(); };
};


#endif /* _GAME_H_ */

/* vim: set ts=8 sts=4 sw=4 et : */
