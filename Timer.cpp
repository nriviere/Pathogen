#include "Timer.h"
#include <Mmsystem.h>
#include <time.h>

Timer::Timer(float tickLength)
{
	previousTime = currentTime = timeGetTime();
	time(&timer);
	time(&prevTimer);
	deltaTime = 0;
	this->tickLength = tickLength;
	tick = false;
}

Timer::Timer(const Timer &timer)
{
	this->previousTime = timer.previousTime;
	this->currentTime = timer.currentTime;
	this->deltaTime = timer.deltaTime;
	this->tickLength = timer.tickLength;
	this->tick = false;
}

Timer &Timer::operator=(const Timer & timer)
{
	Timer::Timer(timer);
	return *this;
}

void Timer::update()
{
	currentTime = timeGetTime();
	time(&timer);

	deltaTime += currentTime - previousTime;
	if (timer - prevTimer >= tickLength)
	{
		tick = true;
		previousTime = currentTime;
		prevTimer = timer;
		deltaTime = 0;
	}
	else
	{
		tick = false;
	}
}

bool Timer::hasTicked()
{
	return tick;
}