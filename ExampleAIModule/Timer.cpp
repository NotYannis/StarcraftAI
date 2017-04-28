#include "Timer.h"


Timer::Timer()
{
	QueryPerformanceFrequency(&frequency);
	startCount.QuadPart = 0;
	endCount.QuadPart = 0;
	stopped = 0;
	startTimeInMicroSec = 0;
	endTimeInMicroSec = 0;

	start();
}


Timer::~Timer()
{
}

void Timer::start()
{
	stopped = 0;
	QueryPerformanceCounter(&startCount);
}

void Timer::stop()
{
	stopped = 1;
	QueryPerformanceCounter(&endCount);
}

double Timer::getElapsedTimeInMS()
{
	if (!stopped)
	{
		QueryPerformanceCounter(&endCount);

		startTimeInMicroSec = startCount.QuadPart * (1000000.0 / frequency.QuadPart);
		endTimeInMicroSec = endCount.QuadPart * (1000000.0 / frequency.QuadPart);
	}
	return (endTimeInMicroSec - startTimeInMicroSec)* 0.001;
}

double Timer::getElapsedTime()
{
	return this->getElapsedTimeInMS()*0.001;
}