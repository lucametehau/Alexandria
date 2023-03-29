#include "eval.h"

// if we don't have enough material to mate consider the position a draw
bool MaterialDraw(const S_Board* pos) {
	//If the board has pawn it's not a draw
	if (CountBits(GetPieceBB(pos, PAWN)))
		return false;
	//If we only have kings on the board then it's a draw
	if (CountBits(Occupancy(pos, BOTH)) == 2)
		return true;

	int bishops = CountBits(GetPieceBB(pos, BISHOP));
	int knights = CountBits(GetPieceBB(pos, KNIGHT));
	int rooks = CountBits(GetPieceBB(pos, ROOK));
	int queens = CountBits(GetPieceBB(pos, QUEEN));

	int white_knights = CountBits(GetPieceColorBB(pos, KNIGHT, WHITE));
	int black_knights = CountBits(GetPieceColorBB(pos, KNIGHT, BLACK));
	int white_bishops = CountBits(GetPieceColorBB(pos, BISHOP, WHITE));
	int black_bishops = CountBits(GetPieceColorBB(pos, BISHOP, BLACK));
	int white_rooks = CountBits(GetPieceColorBB(pos, ROOK, WHITE));
	int black_rooks = CountBits(GetPieceColorBB(pos, ROOK, BLACK));

	if (!rooks && !queens) {

		if (!bishops) {
			if (white_knights < 3 && black_knights < 3)
				return true;
		}
		else if ((!knights && abs(white_bishops - black_bishops) < 2)
			|| ((white_knights + white_bishops == 1) && (black_knights + black_bishops == 1)))
			return true;
	}
	else if (!queens) {
		if (white_rooks == 1 && black_rooks == 1) {
			if ((white_knights + white_bishops) < 2
				&& (black_knights + black_bishops) < 2)
				return true;
		}
		else if (white_rooks == 1 && !black_rooks) {
			if ((white_knights + white_bishops) == 0
				&& (((black_knights + black_bishops) == 1)
					|| (black_knights + black_bishops) == 2))
				return true;
		}
		else if (!white_rooks
			&& black_rooks == 1
			&& (black_knights + black_bishops) == 0
			&& (((white_knights + white_bishops) == 1) || (white_knights + white_bishops) == 2))
			return true;
	}

	return false;
}

// position evaluation
int EvalPosition(const S_Board* pos) {

	if (MaterialDraw(pos)) return 0;

	return (pos->side == WHITE) ? nnue.output(pos->accumulator) : -nnue.output(pos->accumulator);
}