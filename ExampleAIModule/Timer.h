#pragma once
#include <windows.h>

class Timer
{
	double startTimeInMicroSec;                 // starting time in micro-second
	double endTimeInMicroSec;                   // ending time in micro-second
	int    stopped;                             // stop flag 
	LARGE_INTEGER frequency;                    // ticks per second
	LARGE_INTEGER startCount;                   //
	LARGE_INTEGER endCount;                     //

public:
	Timer();
	~Timer();
	void start();
	void stop();
	double getElapsedTimeInMS();
	double getElapsedTime();

};

