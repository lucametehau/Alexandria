#pragma once
#include "nnue_probe.h"
#include "types.h"
#include "Board.h"
#include "search.h"

int evaluate_nnue(const S_Board* pos);

int evaluate_fen_nnue(char* fen);

void init_nnue(char* filename);
