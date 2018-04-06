#pragma once


#include <SDL.h>
#include <ostream>

#include "SDL_ImageLibrary.h"
#include "SDL_TextToFont.h"
#include "SDL_AudioLibrary.h"
#include "Globals.h"

class SDL_GraphicsLibrary
{

public:
	SDL_GraphicsLibrary(std::ostream&);
	bool Init();
	bool InitWindow(std::string& title, int screenWidth, int screenHeight, int screenScale, uint32_t windowFlags);
	bool CreateRender();
	void Quit();

	void CleanUp();
	void CleanTexture(SDL_Texture *texture);
	void CleanSurface(SDL_Surface *surface);
	bool SetUpLogicalSize(int width, int height);

	bool InitTextToFontLibrary();
	bool InitAudioLibrary();
	bool InitImageGraphics();


	void Draw();
	void ClearScreen();

private:
	std::ostream* m_output;
	SDL_Window *m_Window;
	SDL_Renderer *m_Renderer;
};
