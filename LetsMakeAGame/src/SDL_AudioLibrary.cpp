#include "SDL_AudioLibrary.h"


SDL_AudioLibrary::SDL_AudioLibrary(std::ostream& output)
:	m_output( &output)
{
}

bool SDL_AudioLibrary::Init()
{	//initialise sdl mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		(*m_output) << "sdl mixer did not initialise" << std::endl;
		return false;
	}

	return true;
}
