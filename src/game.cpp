#include "game.h"

bool Game::IsValid(int i, int j, Cell current) {
    return Visit(i, j, current, true);
}

bool Game::Play(int i, int j, Cell current) {
    bool move_okay = Visit(i, j, current, false);

    if (move_okay)
        _current_player = (_current_player == Black ? White : Black);

    return move_okay;
}

bool Game::Visit(int i, int j, Cell current, bool test) {
    bool valid = false;

    assert(current != Empty);

    if (_grid.GetCell(i, j) != Empty)
        return false;

    valid |= VisitWorker(i, j, -1, -1, current, test, 0);
    valid |= VisitWorker(i, j, -1,  0, current, test, 0);
    valid |= VisitWorker(i, j, -1,  1, current, test, 0);
    valid |= VisitWorker(i, j,  0,  1, current, test, 0);
    valid |= VisitWorker(i, j,  1,  1, current, test, 0);
    valid |= VisitWorker(i, j,  1,  0, current, test, 0);
    valid |= VisitWorker(i, j,  1, -1, current, test, 0);
    valid |= VisitWorker(i, j,  0, -1, current, test, 0);

    if (not test and valid)
        _grid.SetCell(i, j, current);

    return valid;
}

bool Game::VisitWorker(
    int i, int j, int di, int dj, const Cell &current,
    bool test, int count
) {
    Cell next = _grid.GetCell(i + di, j + dj);

    if (next == Empty)
        return false;

    if (next == current)
        return count != 0;

    if (VisitWorker(i + di, j + dj, di, dj, current, test, count + 1)) {
        if (not test)
            _grid.SetCell(i + di, j + dj, current);
        return true;
    }

    return false;
}

bool Game::IsFinished() {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (IsValid(i, j, Black) or IsValid(i, j, White))
                return false;

    return true;
}

ostream& operator<<(ostream& os, const Game& g) {
    g.Print();
    return os;
}

/* vim: set ts=8 sts=4 sw=4 et : */
