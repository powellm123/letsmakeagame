
#include "SDL_GraphicsLibrary.h"


SDL_GraphicsLibrary::SDL_GraphicsLibrary(std::ostream& output)
{
	m_output = &output;
}

bool SDL_GraphicsLibrary::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		(*m_output) << "error initializeing SDL" << std::endl;
		return false;
	}

	return true;
}
bool SDL_GraphicsLibrary::InitWindow(std::string& title, int screenWidth, int screenHeight, int screenScale, uint32_t windowFlags)
{
	m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth * screenScale, screenHeight * screenScale, windowFlags);

	if(m_Window == nullptr)
	{
		(*m_output) << "Window Error" << std::endl;
		return false;
	}

	return true;
}
bool SDL_GraphicsLibrary::CreateRender()
{
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		(*m_output) << "renderer Error" << std::endl;
		return false;
	}
	Globals::Renderer = m_Renderer;
	return true;
}

bool SDL_GraphicsLibrary::SetUpLogicalSize(int width, int height)
{
	//Size to draw things before we scale it to screen size dimensions mentioned in createWindow
	SDL_RenderSetLogicalSize(m_Renderer, width, height);
	return true;
}

void SDL_GraphicsLibrary::CleanUp()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
	}

	if (m_Window != nullptr)
	{
		SDL_DestroyWindow(m_Window);
	}

	
}
void SDL_GraphicsLibrary::CleanTexture(SDL_Texture *tex) {
	if (!tex) {
		return;
	}
	SDL_DestroyTexture(tex);
}
void SDL_GraphicsLibrary::CleanSurface(SDL_Surface *surf) {
	if (!surf) {
		return;
	}
	SDL_FreeSurface(surf);
}


void SDL_GraphicsLibrary::Quit()
{
	CleanUp();
	SDL_Quit();
}

bool SDL_GraphicsLibrary::InitTextToFontLibrary()
{
	ITextToFontLibrary* sdl_ttf = new SDL_TextToFontLibrary(*m_output);
	return sdl_ttf->Init();
}
bool SDL_GraphicsLibrary::InitAudioLibrary()
{
	IAudioLibrary *sdl_al = new SDL_AudioLibrary(*m_output);
	return sdl_al->Init();
}
bool SDL_GraphicsLibrary::InitImageGraphics()
{
	IImageGraphics<SDL_Renderer, SDL_Texture>* sdl_il = new SDL_ImageLibrary(*m_output);
	return sdl_il->Init();
}



void SDL_GraphicsLibrary::Draw() {

}
void SDL_GraphicsLibrary::ClearScreen() {

}

