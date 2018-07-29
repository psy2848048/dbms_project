#pragma once
#include <ctime>
class ClockChecker{
private :
	clock_t startClock;
	clock_t endClock;

public:
	void SetStartClock();
	void SetEndClock();
	clock_t ElapsedClock();
};