#pragma once

#include <iostream>
#include <SDL.h>

class TimeController
{
public:
	static const int PLAY_STATE, PAUSE_STATE;
	static const int DEBUG_STATE;

	int TimeState;
	Uint32 LastUpdate; // Last time we check ticks we were up to
	float DeltaTime; //in seconds, time since the last frame was rendered onto screen

	void UpdateTime();
	void Pause();
	void Resume();
	void Reset();

	static TimeController instance;
	TimeController();
};