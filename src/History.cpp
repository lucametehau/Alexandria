#include "History.h"


//Update the history heuristics of all the quiet moves passed to the function
void updateHH(const S_Board* pos, Search_data* sd, const int depth, const int bestmove, const S_MOVELIST* quiet_moves) {
	//define the history bonus
	int bonus = std::min(200 * depth, 1962);
	//Loop through all the quiet moves
	for (int i = 0; i < quiet_moves->count; i++)
	{
		int move = quiet_moves->moves[i].move;
		//Scale the history bonus in order to cap the history value to +-32768
		bonus = bonus - getHHScore(pos, sd, move) * abs(bonus) / 16384;
		//We increase the score for the bestmove
		if (move == bestmove) {
			sd->searchHistory[pos->side][From(bestmove)]
				[To(bestmove)] += bonus;
		}
		// and decrease it for all the others
		else {
			sd->searchHistory[pos->side][From(move)]
				[To(move)] -= bonus;
		}
	}
}

//Returns the history score of a move
int getHHScore(const S_Board* pos, const Search_data* sd, const int  move) {
	return sd->searchHistory[pos->side][From(move)][To(move)];
}
//Resets the history table
void cleanHistory(Search_data* ss) {
	//For every piece [12] moved to every square [64] we reset the searchHistory value
	for (int index = 0; index < 64; ++index) {
		for (int index2 = 0; index2 < 64; ++index2) {
			ss->searchHistory[0][index][index2] = 0;
			ss->searchHistory[1][index][index2] = 0;
		}
	}
}