#pragma once
#include "stdafx.h"
#include <time.h>

class Timer
{
private:
	DWORD previousTime, currentTime, deltaTime, tickLength;
	time_t timer,prevTimer;
	bool tick;
	float timePassed;
public:
	Timer(float tickLength = 5);

	Timer(const Timer &timer);

	Timer &operator=(const Timer & timer);

	void update();
	void update(float fDt);

	bool hasTicked();
};