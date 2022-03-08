#ifndef _GRID_H_
#define _GRID_H_

#include <iostream>
using namespace std;

enum Cell {
    Empty,
    Black,
    White
};

class Grid {
private:
    Cell _grid[8][8];

public:
    Grid();
    void Print() const;
    Cell SetCell(int i, int j, Cell cell) { return _grid[i][j] = cell; };
    Cell GetCell(int i, int j) const;
};

#endif /* _GRID_H_ */

/* vim: set ts=8 sts=4 sw=4 et : */
