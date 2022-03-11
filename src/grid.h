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

ostream& operator<<(ostream& os, const Cell &cell);

#define BULLET "\u25cf"
#define WHITE "\033[0;31m"
#define NORMAL "\033[0;0m"
#define LV_PIPE "\u258f"
#define RV_PIPE "\u2595"
#define TH_PIPE "\u2581"
#define BH_PIPE "\u2594"

#endif /* _GRID_H_ */

/* vim: set ts=8 sts=4 sw=4 et : */
