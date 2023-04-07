#include "time_manager.h"
#include "search.h"
#include <algorithm>
#include "misc.h"

//Calculate how much time to spend on searching a move
void Optimum(S_SearchINFO* info, int time, int inc) {
	//Safety overhead to avoid the engine timing out when comunicating with the GUI
	int safety_overhead = 50;
	//if we recieved a movetime command we need to spend exactly that amount of time on the move, so we don't scale
	if (info->movetimeset)
	{
		time -= safety_overhead;
		info->stoptimeMax = info->starttime + time;
		info->stoptimeOpt = info->starttime + time;
	}
	//else If we recieved a movestogo parameter we use total_time/movestogo
	else if (info->timeset && info->movestogo != -1)
	{
		time -= safety_overhead;
		//Divide the time you have left for how many moves you have to play
		auto basetime = time / info->movestogo;
		//Never use more than 80% of the total time left for a single move
		auto maxtimeBound = 0.8 * time;
		//optime is the time we use to stop if we just cleared a depth
		auto optime = std::min(0.7 * basetime, maxtimeBound);
		//maxtime is the absolute maximum time we can spend on a search (unless it is bigger than the bound)
		auto maxtime = std::min(3.0 * basetime, maxtimeBound);
		info->stoptimeMax = info->starttime + maxtime;
		info->stoptimeOpt = info->starttime + optime;
	}
	// else if we recieved wtime/btime we calculate an over and upper bound for the time usage based on fixed coefficients
	else if (info->timeset)
	{
		time -= safety_overhead;
		int basetime = time / 20 + inc / 2;
		//optime is the time we use to stop if we just cleared a depth
		int optime = basetime * 0.6;
		//maxtime is the absolute maximum time we can spend on a search
		int maxtime = std::min(time, basetime * 2);
		info->stoptimeMax = info->starttime + maxtime;
		info->stoptimeOpt = info->starttime + optime;
	}
}

bool StopEarly(const S_SearchINFO* info)
{
	// check if we used all the nodes/movetime we had or if we used more than our lowerbound of time
	if ((info->timeset || info->movetimeset) && GetTimeMs() > info->stoptimeOpt)
		return true;
	else return false;
}

bool NodesOver(const S_SearchINFO* info) {
	// check if we used all the nodes/movetime we had or if we used more than our lowerbound of time
	if (info->nodeset == TRUE && info->nodes > info->nodeslimit)
		return true;
	else return false;
}

bool TimeOver(const S_SearchINFO* info) {
	// check if more than Maxtime passed and we have to stop
	if (NodesOver(info)) return true;
	if (((info->timeset || info->movetimeset)
		&& ((info->nodes & 1023) == 1023)
		&& GetTimeMs() > info->stoptimeMax))
		return true;
	else return false;
}