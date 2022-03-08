#include "grid.h"

Grid::Grid() {
    for (auto &line:_grid)
        for (auto &cell:line)
            cell = Empty;

    _grid[3][3] = _grid[4][4] = White;
    _grid[3][4] = _grid[4][3] = Black;
}

Cell Grid::GetCell(int i, int j) const {
    if (i < 0 || i > 7 || j < 0 || j > 7)
        return Empty;
    return _grid[i][j];
};

void Grid::Print() const {
    char sym;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            switch(_grid[i][j]) {
            case Black:
                sym = 'x';
                break;

            case White:
                sym = 'o';
                break;

            case Empty:
                sym = ' ';
                break;
            }
            cout << sym;
        }
        cout << endl;
    }
}

/* vim: set ts=8 sts=4 sw=4 et : */
