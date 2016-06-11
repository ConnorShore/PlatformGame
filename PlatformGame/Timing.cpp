#include "Timing.h"

#include <SDL/SDL.h>
#include <cstdio>
#include <iostream>

Timing::Timing()
{
}

void Timing::FpsLimitInit()
{
	_initTick = SDL_GetTicks();
}

void Timing::TimeInit()
{
	_fpsLastTime = SDL_GetTicks();
	_fpsCurrent = 0;
	_fpsFrames = 0;
}

void Timing::CalculateFPS(bool printFPS)
{
	_fpsFrames++;

	if (_fpsLastTime < SDL_GetTicks() - (1.0f * 1000.0f)) {
		_fpsLastTime = SDL_GetTicks();
		_fpsCurrent = _fpsFrames;

		if (printFPS)
			printf("%u\n", _fpsCurrent);

		_deltaTime = float(_fpsCurrent - _fpsLastTime);

		_fpsFrames = 0;
	}
}

void Timing::LimitFPS(const float MAX_FPS)
{
	unsigned int ticks = SDL_GetTicks() - _initTick;

	if (1000.0f / MAX_FPS > ticks) {
		SDL_Delay(1000.0f / MAX_FPS - ticks);
	}
}

void Timing::calcDeltaTime()
{
	static long last = 0;
	_deltaTime = 0.0f;

	long now = SDL_GetTicks();
	if (now > last) {
		_deltaTime = ((float)(now - last)) / 1000.0f;
		last = now;
	}
}

Timing::~Timing()
{
}
