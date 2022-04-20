#ifndef TIMER_H
#define TIMER_H
#include "variables.h"

class Timer
{
private:
	Uint32 mStartTicks;
	Uint32 mPausedTicks;

	bool mPaused;
	bool mStarted;

public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	bool reached(int count);
	void regulate(int fps);

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();
};

#endif