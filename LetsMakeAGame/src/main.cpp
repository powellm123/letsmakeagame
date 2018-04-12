#include <iostream>
#include "SDL_GraphicsLibrary.h"
#include "Game.h"
#include "Globals.h"
#include <time.h>


int main(int argc, char **argv)
{
	//set the random seed for the random number sequence
	srand(time(0));

	Globals::Debugging = false;
	Globals::ScreenWidth = 640;
	Globals::ScreenHeight = 512;
	Globals::ScreenScale = 2;
	Globals::TileWidth = 32;
	Globals::TileHeight = 32;
	   
	SDL_GraphicsLibrary *sdl_gl = new SDL_GraphicsLibrary(std::cout);
	std::string windowName = std::string("Lets make a game");
	if (!sdl_gl->Init()
		|| !sdl_gl->InitWindow(windowName, Globals::ScreenWidth, Globals::ScreenHeight, Globals::ScreenScale,  SDL_WINDOW_SHOWN )
		|| !sdl_gl->CreateRender()
		
		|| !sdl_gl->SetUpLogicalSize(Globals::ScreenWidth, Globals::ScreenHeight)
		|| !sdl_gl->InitImageGraphics()
		|| !sdl_gl->InitAudioLibrary()
		|| !sdl_gl->InitTextToFontLibrary())
	{
		sdl_gl->Quit();
		return 1;
	}

	Game *game = new Game(sdl_gl);
	game->Run();

	sdl_gl->Quit();

	return 0;
}