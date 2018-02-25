#include "SDL_TextToFont.h"


SDL_TextToFontLibrary::SDL_TextToFontLibrary(std::ostream& output)
	: m_output(&output)
{
}

bool SDL_TextToFontLibrary::Init()
{
	//Initialise text to font
	if (TTF_Init() != 0)
	{
		(*m_output) << "sdl ttf did not initialise" << std::endl;
		return false;
	}
	return true;
}