#ifndef _GAME_H_
#define _GAME_H_

#include "grid.hpp"
#include <cassert>

// Game object
class Game {
private:
    Grid _grid;
    Cell _current_player = Black;
    int _black_amount = 2, _white_amount = 2;

public:
    bool Play(int i, int j, Cell current);
    bool Visit(int i, int j, Cell current, bool test);
    bool MoveAvailable(int i, int j, Cell current);
    bool VisitWorker(
        int i, int j, int di, int dj, const Cell& current, bool test, int count
    );
    bool IsFinished();
    bool CanPlay(Cell player);
    void Print() const { _grid.Print(); };
    Cell GetPlayer() const { return _current_player; };
    Cell GetCell(int i, int j) const { return _grid.GetCell(i, j); };
    int GetScore(Cell player) const;
    friend ostream& operator<<(ostream& os, const Game& g);
};

#endif /* _GAME_H_ */

/* vim: set ts=8 sts=4 sw=4 et : */