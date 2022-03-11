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
}

void Grid::Print() const {
    // grid x label
    cout << "\n ";
    for (int i = 0; i < 8; ++i)
        cout << " " << char('a' + i) << " ";
    cout << endl;

    // top border
    for (int i = 0; i < 8*3 + 2; ++i)
        cout << TH_PIPE;
    cout << endl;

    // grid
    for (int i = 0; i < 8; ++i) {
        const char *cell;

        cout << LV_PIPE;
        for (int j = 0; j < 8; ++j) {
            switch(_grid[i][j]) {
            case Black:
                cell = " " BULLET " ";
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
        // grid y label
        cout << RV_PIPE << "  " << i + 1 << endl;
    }

    // bottom border
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
        throw 1; /* Printing empty cell */
    }

    return os;
}

/* vim: set ts=8 sts=4 sw=4 et : */
