#include "nnue_eval.h"
#include "nnue_probe.h"
#include "types.h"
#include "Board.h"
#include "search.h"
#include <iostream>

void init_nnue(char* filename) {
	nnue_init(filename);
}

int mapped_pieces[12] = { 6, 5, 4, 3, 2, 1, 12, 11, 10, 9, 8, 7 };
int mapped_squares[64] = {
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};


int map_piece_to_probe(int piece) {
	return mapped_pieces[piece];
}

int map_square_to_probe(int square) {
	return mapped_squares[square];
}

void populate_piece_square_arrays(const S_Board* pos, int* pieces, int* squares)
{
	int spot = 2;
	int count = 0;
	for (int i = 0;i < Board_sq_num;i++) {
		int piece = pos->pieces[i];
		if (piece == EMPTY) continue;
		else if (piece == WK) 
		{
			pieces[0] = map_piece_to_probe(WK);
			squares[0] = map_square_to_probe(i);
		}
		else if (piece == BK) 
		{
			pieces[1] = map_piece_to_probe(BK);
			squares[1] = map_square_to_probe(i);
		}
		else 
		{
			piece = map_piece_to_probe(piece);
			pieces[spot] = piece;
			squares[spot] = map_square_to_probe(i);
			spot++;
		}

		count++;
	}
	pieces[count] = 0;
	squares[count] = 0;
	return;
}


//Takes in a board, extracts the requires value and lets the probe library handle the eval
int evaluate_nnue(const S_Board* pos)
{
	int pieces[33];
	int squares[33];
	int player = pos->side;
	populate_piece_square_arrays(pos, pieces, squares);
	return nnue_evaluate(player, pieces, squares);
}

int evaluate_fen_nnue(char* fen) {
	return nnue_evaluate_fen(fen);
}

