#include "game.h"

bool Game::Play(int i, int j, Cell current) {
    bool valid = false;

    assert(current != Empty);

    if (_grid.GetCell(i, j) != Empty)
        return false;

    _grid.SetCell(i, j, current);

    valid |= Visit(i, j, -1, -1, current);
    valid |= Visit(i, j, -1,  0, current);
    valid |= Visit(i, j, -1,  1, current);
    valid |= Visit(i, j,  0,  1, current);
    valid |= Visit(i, j,  1,  1, current);
    valid |= Visit(i, j,  1,  0, current);
    valid |= Visit(i, j,  1, -1, current);
    valid |= Visit(i, j,  0, -1, current);

    if (!valid)
        _grid.SetCell(i, j, Empty);

    return valid;
}

bool Game::Visit(int i, int j, int di, int dj, const Cell &current) {
    Cell next = _grid.GetCell(i + di, j + dj);

    if (next == Empty)
        return false;

    if (next == current)
        return true;

    if (Visit(i + di, j + dj, di, dj, current)) {
        _grid.SetCell(i + di, j + dj, current);
        return true;
    }

    return false;
}

/* vim: set ts=8 sts=4 sw=4 et : */
