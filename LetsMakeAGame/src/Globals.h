#pragma once
#include <string>
#include <windows.h>
#include "SDL.h"
#include "Buttons.h"

class Globals
{
public:
	static Buttons *ControllerButtons;
	static Buttons *KeyboardButtons;
	static bool Quit;
	static bool Debugging;
	static int ScreenWidth, ScreenHeight, ScreenScale;
	static int TileWidth, TileHeight;
	static SDL_Surface* MainSurface;
	static SDL_Renderer *Renderer;
	static std::string GetResourcePath();
	static size_t GenerateId();
	static char IntToChar(int number);
};