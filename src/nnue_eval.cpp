#include "nnue_eval.h"
#include "nnue_probe.h"
#include "types.h"
#include "Board.h"
#include "search.h"

void init_nnue(char* filename) {
	nnue_init(filename);
}

int evaluate_nnue(int player, int* pieces, int* squares) {
	return 0;
}

int evaluate_fen_nnue(char* fen) {
	return nnue_evaluate_fen(fen);
}

