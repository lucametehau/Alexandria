#include "eval.h"

// if we don't have enough material to mate consider the position a draw
bool MaterialDraw(const S_Board* pos) {

	return false;
}

// position evaluation
int EvalPosition(const S_Board* pos) {
	return (pos->side == WHITE) ? nnue.output(pos->accumulator) : -nnue.output(pos->accumulator);
}