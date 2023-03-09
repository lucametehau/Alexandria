#include "eval.h"

// if we don't have enough material to mate consider the position a draw
int MaterialDraw(const S_Board* pos) {
	//If we only have kings on the board then it's a draw
	if (CountBits(Occupancy(pos, BOTH)) == 2)
		return TRUE;
	else if (CountBits(Occupancy(pos, BOTH)) == 3 && ((CountBits(GetPieceBB(pos, KNIGHT)) == 1) || (CountBits(GetPieceBB(pos, BISHOP)) == 1)))
		return TRUE;

	return FALSE;
}

// position evaluation
int EvalPosition(const S_Board* pos, S_SearchINFO* info) {
	int white_pawns = CountBits(GetPieceColorBB(pos, PAWN, WHITE));
	int black_pawns = CountBits(GetPieceColorBB(pos, PAWN, BLACK));

	int white_bishops = CountBits(GetPieceColorBB(pos, BISHOP, WHITE));
	int black_bishops = CountBits(GetPieceColorBB(pos, BISHOP, BLACK));

	int white_knights = CountBits(GetPieceColorBB(pos, KNIGHT, WHITE));
	int black_knights = CountBits(GetPieceColorBB(pos, KNIGHT, BLACK));

	int white_rooks = CountBits(GetPieceColorBB(pos, ROOK, WHITE));
	int black_rooks = CountBits(GetPieceColorBB(pos, ROOK, BLACK));

	int white_queens = CountBits(GetPieceColorBB(pos, QUEEN, WHITE));
	int black_queens = CountBits(GetPieceColorBB(pos, QUEEN, BLACK));

	int score = white_pawns - black_pawns
		+ (white_bishops - black_bishops) * 3
		+ (white_knights - black_knights) * 3
		+ (white_rooks - black_rooks) * 5
		+ (white_queens - black_queens) * 9;
	score *= 100;
	//random term
	score += (2 * (info->nodes & 3) - 3);

	return (pos->side == WHITE) ? score : -score;
}