#include "eval.h"

// if we don't have enough material to mate consider the position a draw
bool MaterialDraw(const S_Board* pos) {
	//If the board has pawn it's not a draw
	if (CountBits(GetPieceBB(pos, PAWN)))
		return false;
	//If we only have kings on the board then it's a draw
	if (CountBits(Occupancy(pos, BOTH)) == 2)
		return true;


	int rooks = CountBits(GetPieceBB(pos, ROOK));
	int queens = CountBits(GetPieceBB(pos, QUEEN));

	if (!rooks && !queens) {
		int bishops = CountBits(GetPieceBB(pos, BISHOP));
		int knights = CountBits(GetPieceBB(pos, KNIGHT));
		int white_knights = CountBits(GetPieceColorBB(pos, KNIGHT, WHITE));
		int black_knights = CountBits(GetPieceColorBB(pos, KNIGHT, BLACK));
		int white_bishops = CountBits(GetPieceColorBB(pos, BISHOP, WHITE));
		int black_bishops = CountBits(GetPieceColorBB(pos, BISHOP, BLACK));
		if (!bishops) {
			if (white_knights < 3 && black_knights < 3)
				return true;
		}
		else if ((!knights && abs(white_bishops - black_bishops) < 2)
			|| ((white_knights + white_bishops == 1) && (black_knights + black_bishops == 1)))
			return true;
	}

	return false;
}

// position evaluation
int EvalPosition(const S_Board* pos) {

	if (MaterialDraw(pos)) return 0;

	return (pos->side == WHITE) ? nnue.output(pos->accumulator) : -nnue.output(pos->accumulator);
}