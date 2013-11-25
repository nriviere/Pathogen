#pragma once
#include "stdafx.h"
#include <time.h>

class Timer
{
private:
	DWORD previousTime, currentTime, deltaTime, tickLength;
	time_t timer,prevTimer;
	bool tick;
public:
	Timer(float tickLength = 5);

	Timer(const Timer &timer);

	Timer &operator=(const Timer & timer);

	void update();

	bool hasTicked();
};