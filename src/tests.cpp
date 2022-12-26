#include "Board.h"
#include "search.h"
#include "ttable.h"
#include <iostream>
#include "init.h"
#include "misc.h"



void fifty_mr_test() {

	const char* testfens[4] = {
	"7k/8/R7/1R6/7K/8/7P/8 w - - 99 1",
	"8/7p/8/7k/1r6/r7/8/7K b - - 99 1",
	"8/8/8/P7/8/6n1/3R4/R3K2k w Q - 99 1",
	"r3k2K/3r4/6N1/8/p7/8/8/8 b q - 99 1"
	}

		// init all
	init_all();
	S_UciOptions uci_options[1];
	S_ThreadData td[1];
	int total_nodes = 0;
	int total_time = 0;
	InitHashTable(HashTable, 64);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	for (int positions = 0; positions < 4; positions++) {
		parse_fen(testfens[positions], &td->pos);

		printf("\nPosition: %d\n", positions);

		Root_search_position(2, td, uci_options);

		total_nodes += td->info.nodes;
		total_time += GetTimeMs() - td->info.starttime;
	}

	std::cout << "\n"
		<< total_nodes << " nodes "
		<< total_nodes / ((total_time / 1000) + 1) << " nps " << std::endl;
	return 0;
}





void run_tests()
{
	fifty_mr_test();
}


