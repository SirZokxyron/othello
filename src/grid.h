#ifndef _GRID_H_
#define _GRID_H_

#include <iostream>
using namespace std;

// Cell enum type represents one cell of the grid
enum Cell {
    Empty,
    Black,
    White
};

// Grid object
class Grid {
private:
    Cell _grid[8][8];

public:
    Grid();
    void Print() const;
    // Basic setter/getter to manipulate the object later on
    Cell SetCell(int i, int j, Cell cell) { return _grid[i][j] = cell; };
    Cell GetCell(int i, int j) const;
};

// << overload to ease the display of the current player
ostream& operator<<(ostream& os, const Cell &cell);

// Symbols and macros used to display the grid in the terminal
#define BULLET "\u25cf"     // Unicode char: https://unicode-explorer.com/c/25CF
#define WHITE "\033[0;37m"  // ANSI esc code for the white color
#define BLACK "\033[0;30m"  // ANSI esc code for the black color
#define NORMAL "\033[0;0m"  // ANSI esc code to revert the color
#define LV_PIPE "\u258f"    // Unicode char: https://unicode-explorer.com/c/258F
#define RV_PIPE "\u2595"    // Unicode char: https://unicode-explorer.com/c/2595
#define TH_PIPE "\u2581"    // Unicode char: https://unicode-explorer.com/c/2581
#define BH_PIPE "\u2594"    // Unicode char: https://unicode-explorer.com/c/2594

#endif /* _GRID_H_ */

/* vim: set ts=8 sts=4 sw=4 et : */
