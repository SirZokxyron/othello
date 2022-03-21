#include "computer.hpp"

ostream& operator<<(ostream& os, Move& m) { 
	os << "(" <<m._i << ", " << m._j << ")"; 
	return os;
}

Move Computer::GetBestMove(Game g) const {
	Move best = Move(0, 0);
	int best_score = -65;
	int score;
	int alpha = -65;
	int beta = 65;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (g.MoveAvailable(i, j, _color)) {
				score = MinMaxAB(g, i, j, MAX_REC, alpha, beta);
				// cout << score << endl;
				if (score > best_score) {
					best_score = score;
					best = Move(i, j);
				}
				if (best_score >= beta)
					return best;
				if (best_score > alpha)
					alpha = best_score;
			}
	return best;
}

int Computer::MinMaxAB(Game g, int pre_i, int pre_j, int depth, int alpha, int beta) const {
	g.Play(pre_i, pre_j, g.GetPlayer());
	if (depth == 0 || g.IsFinished())
        return g.GetScore(g.GetPlayer());
    int best_score, score;
	if (g.GetPlayer() == _color) {
		best_score = -65;
        for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
				if (g.MoveAvailable(i, j, g.GetPlayer())) {
					score = MinMaxAB(g, i, j, depth-1, alpha, beta);
					if (best_score < score)
						best_score = score;
					if (best_score >= beta)
						return best_score;
					if (best_score > alpha)
						alpha = best_score;
				}
        return best_score;
	} else {
		best_score = 65;
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
				if (g.MoveAvailable(i, j, g.GetPlayer())) {
					score = MinMaxAB(g, i, j, depth-1, alpha, beta);
					if (score < best_score)
						best_score = score;
					if (best_score <= alpha)
						return best_score;
					if (beta < best_score)
						beta = best_score;
				}
        return best_score;
	} 
}

/* vim: set ts=8 sts=4 sw=4 et : */
