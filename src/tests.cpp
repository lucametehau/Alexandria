#include "Board.h"
#include "search.h"
#include "ttable.h"
#include <iostream>
#include "init.h"
#include "misc.h"

using pair_type = std::pair<std::string, std::string>;


//Runs a generic test matching a searching position X for bestmove X
void run_test(const std::string testfen, const  std::string best_move) {
	// init all;
	init_all();
	S_UciOptions uci_options[1];
	S_ThreadData td[1];
	InitHashTable(HashTable, 64);

	parse_fen(testfen.c_str(), &td->pos);

	Root_search_position(3, td, uci_options);

	int bestmove = getBestMove(&td->ss);

	assert(bestmove == parse_move(const_cast<char*>(best_move.c_str()), &td->pos));

	return;
}

void fifty_mr_test() {

	printf("\n50 MR TEST\n");
	const std::array<pair_type, 4> tests = { {
		   {"7k/8/R7/1R6/7K/8/7P/8 w - - 99 1", "h2h3"},
		   {"8/7p/8/7k/1r6/r7/8/7K b - - 99 1", "h7h6"},
		   {"8/8/8/P7/8/6n1/3R4/R3K2k w Q - 99 1", "a5a6"},
		   {"r3k2K/3r4/6N1/8/p7/8/8/8 b q - 99 1", "a4a3"},
	   } };

	for (const auto& [fen, movestr] : tests) {
		run_test(fen, movestr);
	}
}

void mate_test() {

	printf("\nMATE TEST\n");
	const std::array<pair_type, 4> tests = { {
		{"3k4/8/3K4/8/5R2/8/8/8 w - - 0 1", "f4f8"},
		{"8/8/8/5r2/8/3k4/8/3K4 b - - 0 1", "f5f1"},
		{"1k1r2R1/8/1K6/8/8/8/8/8 w - - 0 1", "g8d8"},
		{"8/8/8/8/8/1k6/8/1K1R2r1 b - - 0 1", "g1d1"},
	} };

	for (const auto& [fen, movestr] : tests) {
		run_test(fen, movestr);
	}
}


void mate_test_castling() {
	printf("\nMATE TEST CASTLING EDITION\n");

	const std::array<pair_type, 4> tests = { {
		  {"8/8/8/8/8/8/7R/1k2K2R w K - 0 1", "e1g1"},
		  {"1K2k2r/7r/8/8/8/8/8/8 b k - 0 1", "e8g8"},
		  {"8/8/8/8/8/8/R7/R3K2k w Q - 0 1", "e1c1"},
		  {"r3k2K/r7/8/8/8/8/8/8 b q - 0 1", "e8c8"},
	  } };

	for (const auto& [fen, movestr] : tests) {
		run_test(fen, movestr);
	}
}

void stalemate_test() {
	printf("\nSTALEMATE TEST\n");
	const std::array<pair_type, 6> tests = { {
	   {"kb4r1/p7/8/8/8/6q1/8/R6K w - - 0 1", "a1a7"},
	   {"r6k/8/6Q1/8/8/8/P7/KB4R1 b - - 0 1", "a8a2"},
	   {"8/8/8/8/8/8/p7/k1K5 w - - 0 1", "c1c2"},
	   {"K1k5/P7/8/8/8/8/8/8 b - - 0 1", "c8c7"},
	   {"K1k5/P1q5/8/B7/8/8/8/8 w - - 0 1", "a5c7"},
	   {"8/8/8/8/b7/8/p1Q5/k1K5 b - - 0 1", "a4c2"},
   } };

	for (const auto& [fen, movestr] : tests) {
		run_test(fen, movestr);
	}
}

void run_tests()
{
	fifty_mr_test();
	mate_test();
	mate_test_castling();
	stalemate_test();


}


