#include "grid.hpp"

Grid::Grid() {
    // Empty init of the array
    for (auto &line:_grid)
        for (auto &cell:line)
            cell = Empty;

    // Setting up the initial pattern
    _grid[3][3] = _grid[4][4] = White;
    _grid[3][4] = _grid[4][3] = Black;
}

Cell Grid::GetCell(int i, int j) const {
    // If the hit is outside the grid, return empty
    if (i < 0 || i > 7 || j < 0 || j > 7)
        return Empty;
    return _grid[i][j]; // Otherwise, return the cell
}

void Grid::Print() const {
    // Grid x label display
    cout << "\n ";
    for (int i = 0; i < 8; ++i)
        cout << " " << char('a' + i) << " ";
    cout << endl;

    // Top border display
    for (int i = 0; i < 8*3 + 2; ++i)
        cout << TH_PIPE;
    cout << endl;

    // Grid display
    for (int i = 0; i < 8; ++i) {
        const char *cell;

        cout << LV_PIPE;
        for (int j = 0; j < 8; ++j) {
            switch(_grid[i][j]) {
            case Black:
                cell = BLACK " " BULLET " " NORMAL;
                break;

            case White:
                cell = WHITE " " BULLET " " NORMAL;
                break;

            case Empty:
                cell = "   ";
                break;
            }
            cout << cell;
        }
        // Grid y label display
        cout << RV_PIPE << "  " << i + 1 << endl;
    }

    // Bottom border display
    for (int i = 0; i < 8*3 + 2; ++i)
        cout << BH_PIPE;
    cout << endl;
}

ostream& operator<<(ostream& os, const Cell &cell) {
    switch(cell) {
    case Black:
        os << "Black";
        break;

    case White:
        os << "White";
        break;

    default:
        throw 1; // Printing empty cell exception
    }

    return os;
}

/* vim: set ts=8 sts=4 sw=4 et : */
