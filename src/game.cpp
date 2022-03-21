#include "game.hpp"

bool Game::MoveAvailable(int i, int j, Cell current) {
    // Testing the move
    return Visit(i, j, current, true);
}

bool Game::Play(int i, int j, Cell current) {
    // Attempting to do the move
    bool move_okay = Visit(i, j, current, false);

    // If the move was valid, switch the player
    if (move_okay) {
        _current_player = (_current_player == Black ? White : Black);
        if (not CanPlay(GetPlayer()))
            _current_player = (_current_player == Black ? White : Black);
    }

    return move_okay;
}

bool Game::Visit(int i, int j, Cell current, bool test) {
    bool isValid, UL, LE, DL, DO, DR, RI, UR, UP;

    // Making sure the current player is not Empty
    assert(current != Empty);

    // Checking if the targeted cell is empty
    if (_grid.GetCell(i, j) != Empty)
        return false;

    // Checking if the move would flip a cell in all 8 directions
    UL = VisitWorker(i, j, -1, -1, current, test, 0); // up   left
    LE = VisitWorker(i, j, -1,  0, current, test, 0); //      left
    DL = VisitWorker(i, j, -1,  1, current, test, 0); // down left
    DO = VisitWorker(i, j,  0,  1, current, test, 0); // down
    DR = VisitWorker(i, j,  1,  1, current, test, 0); // down right
    RI = VisitWorker(i, j,  1,  0, current, test, 0); //      right
    UR = VisitWorker(i, j,  1, -1, current, test, 0); // up   right
    UP = VisitWorker(i, j,  0, -1, current, test, 0); // up
    isValid = UL || LE || DL || DO || DR || RI || UR || UP;

    // If the visit was not a test and the move is valid
    if (not test and isValid) {
        _grid.SetCell(i, j, current);
        (current == Black) ? _black_amount++ : _white_amount++; //! Testing stuff
    }

    return isValid;
}

bool Game::VisitWorker(
    int i, int j, int di, int dj, const Cell &current,
    bool test, int count
) {
    // Getting the next cell in current direction
    Cell next = _grid.GetCell(i + di, j + dj);

    // If it's empty, then the move is wrong
    if (next == Empty)
        return false;

    // If it's the same color as the current player
    if (next == current)
        // Verify that we flipped at least one other player cell
        return count != 0;

    // If it's the other player color, then we visit it, if it's valid
    if (VisitWorker(i + di, j + dj, di, dj, current, test, count + 1)) {
        // If the visit was not a test
        if (not test) {
            // We flip it to the current player color
            _grid.SetCell(i + di, j + dj, current);
            (current == Black) ? _black_amount++ & _white_amount-- : _black_amount-- & _white_amount++; //! Testing stuff
        }
        return true;
    }

    return false;
}

bool Game::CanPlay(Cell player) {
    // For every cell of the grid we check if the player has a move available
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (MoveAvailable(i, j, player))
                return true;

    return false;
}

bool Game::IsFinished() {
    return not(CanPlay(Black) or CanPlay(White));
}

int Game::GetScore(Cell player) const {
    // Protection against error on our side
    assert(player != Empty);
    // The higher a score is, the higher is the advantage of the player in the game
    if (player == Black)
        return _black_amount;
    else
        return _white_amount;
}

ostream& operator<<(ostream& os, const Game& g) {
    g.Print();
    return os;
}

/* vim: set ts=8 sts=4 sw=4 et : */
