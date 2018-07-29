#include "ClockChecker.h"
#include <ctime>

void ClockChecker::SetStartClock(){
	startClock = clock();
}

void ClockChecker::SetEndClock(){
	endClock = clock();
}
clock_t ClockChecker::ElapsedClock(){
	return (endClock - startClock);
}
