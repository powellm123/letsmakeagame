#include "SDL_ImageLibrary.h"


SDL_ImageLibrary::SDL_ImageLibrary(std::ostream& output)
{
	m_output = &output;
}

bool SDL_ImageLibrary::Init()
{
	//Initalise sdl_imageB
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		(*m_output) << "sdl image did not initialise" << std::endl;
		return false;
	}
	return true;
}

SDL_Texture* SDL_ImageLibrary::Load(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr) {
		return nullptr;
	}
	return texture;
}