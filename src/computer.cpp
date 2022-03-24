#include "computer.hpp"

Move Computer::GetBestMove(Game g) const {
    Move best;
    int best_score = -65,
        score,
        alpha = -65,
        beta = 65;
    shared_ptr<vector<Move>> available_moves = g.AvailableMoves();

    // We call minmax on all the available moves
    for (auto &move:*available_moves) {
        score = MinMaxAB(g, move, MAX_REC, alpha, beta);
        if (score > best_score) {
            best_score = score;
            best = Move(move);
        }
        if (best_score >= beta)
            return best; // Minmax pruning
        if (best_score > alpha)
            alpha = best_score;
    }

    return best;
}

int Computer::MinMaxAB(
    Game g, Move move, int depth, int alpha, int beta
) const {
    int best_score, score;
    shared_ptr<vector<Move>> available_moves;

    g.Play(move, g.GetPlayer());

    if (depth == 0 || g.IsFinished())
        return g.GetScore(_color);

    available_moves = g.AvailableMoves();

    if (g.GetPlayer() == _color) {
        // Max branch of the Minmax algo
        best_score = -65;
        for (auto &move:*available_moves) {
            score = MinMaxAB(g, move, depth-1, alpha, beta);
            if (best_score < score)
                best_score = score;
            if (best_score >= beta)
                return best_score; // Minmax Pruning
            if (best_score > alpha)
                alpha = best_score;
        }
        return best_score;
    } else {
        // Min branch of the Minmax algo
        best_score = 65;
        for (auto &move:*available_moves) {
            score = MinMaxAB(g, move, depth-1, alpha, beta);
            if (score < best_score)
                best_score = score;
            if (best_score <= alpha)
                return best_score; // Minmax Pruning
            if (beta < best_score)
                beta = best_score;
        }
        return best_score;
    }
}

/* vim: set ts=8 sts=4 sw=4 et : */
