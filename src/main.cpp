

// system headers
#include "Board.h"
#include "PieceData.h"
#include "attack.h"
#include "hashkey.h"
#include "init.h"
#include "nnue_eval.h"
#include "perft.h"
#include "search.h"
#include "ttable.h"
#include "uci.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

int main([[maybe_unused]] int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	// init all
	init_all();
	std::cout << evaluate_fen_nnue(start_position)<<std::endl;
	InitHashTable(HashTable, 16);
	// connect to the GUI
	Uci_Loop(argv);
	
	return 0;
}
