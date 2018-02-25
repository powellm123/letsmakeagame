#pragma once


#include "GraphicsLibrary.h"
#include <SDL.h>
#include <ostream>

#include "SDL_ImageLibrary.h"
#include "SDL_TextToFont.h"
#include "SDL_AudioLibrary.h"
#include "Globals.h"

class SDL_GraphicsLibrary : public IGraphicsLibrary
{

public:
	SDL_GraphicsLibrary(std::ostream&);
	bool Init() override;
	bool InitWindow(std::string& title, int screenWidth, int screenHeight, int screenScale, uint32_t windowFlags) override;
	bool CreateRender() override;
	void Quit() override;

	void CleanUp() override;
	void CleanTexture(SDL_Texture *texture);
	void CleanSurface(SDL_Surface *surface);
	bool SetUpLogicalSize(int width, int height);

	bool InitTextToFontLibrary() override;
	bool InitAudioLibrary() override;
	bool InitImageGraphics() override;


	void Draw() override;
	void ClearScreen() override;

private:
	std::ostream* m_output;
	SDL_Window *m_Window;
	SDL_Renderer *m_Renderer;
};
