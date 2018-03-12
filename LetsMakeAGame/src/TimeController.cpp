
#include "TimeController.h"

const int TimeController::PLAY_STATE = 1;
const int TimeController::PAUSE_STATE = 0;
const int TimeController::DEBUG_STATE = 2;

TimeController TimeController::instance;

void TimeController::UpdateTime()
{
	if (TimeState == PAUSE_STATE)
	{
		DeltaTime = 0;
	}
	else if (TimeState == DEBUG_STATE)
	{
		DeltaTime = 0.095;
	}

	else {
		Uint32 timeDiff = SDL_GetTicks() - LastUpdate;
		DeltaTime = timeDiff / 1000.0; // move these milliseconds into the decimal place area
		DeltaTime = DeltaTime > .125 ? .125 : DeltaTime;
	}

	LastUpdate = SDL_GetTicks();

}
void TimeController::Pause()
{
	TimeState = PAUSE_STATE;
}
void TimeController::Resume()
{
	TimeState = PLAY_STATE;
}
void TimeController::Reset()
{
	DeltaTime = 0;
	LastUpdate = SDL_GetTicks();
}

TimeController::TimeController()
{
	DeltaTime = 0;
	LastUpdate = 0;
	TimeState = PLAY_STATE;
}