#include "Timer.h"

Timer::Timer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void Timer::start()
{
	//start timer, unpause, get game ticks
	mStarted = true;
	mPaused = false;

	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Timer::stop()
{
	//reset all timer variables
	mStarted = false;
	mPaused = false;

	mStartTicks = mPausedTicks = 0;
}

void Timer::pause()
{
	if(mStarted && !mPaused)
	{
		mPaused = true;
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void Timer::unpause()
{
	if(mStarted && mPaused)
	{
		mPaused = false;
		mStartTicks = SDL_GetTicks() - mPausedTicks;
		mPausedTicks = 0;
	}
}

bool Timer::reached(int count)
{
	if(mStarted)
	{
		if( (SDL_GetTicks() - mStartTicks > count))
		{
			return true;
		}
	}
	return false;
}

void Timer::regulate(int fps)
{
	if(getTicks() < 1000/fps)
	{
		SDL_Delay( (1000/fps) - getTicks() );
	}
}

Uint32 Timer::getTicks()
{
	Uint32 time=0;

	if(mStarted)
	{
		if(mPaused)
		{
			time = mPausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - mStartTicks;
		}
	}
	return time;
}

bool Timer::isStarted()
{
	return mStarted;
}

bool Timer::isPaused()
{
	return mPaused && mStarted;
}