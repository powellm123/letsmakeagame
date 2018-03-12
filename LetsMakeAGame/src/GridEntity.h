#pragma once

#include "SDL.h"

struct GridEntity
{
	SDL_Point loc;
	float angle;
	GridType gridType;
};