#pragma once
#include <string>
#include <windows.h>
#include "SDL.h"

class Globals
{
public:
	static bool Debugging;
	static int ScreenWidth, ScreenHeight, ScreenScale;
	static SDL_Renderer *Renderer;
	static std::string GetResourcePath();
	static std::string GenerateId();
};