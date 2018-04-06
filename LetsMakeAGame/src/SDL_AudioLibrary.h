#pragma once

#include <ostream>
#include "SDL_mixer.h"

class SDL_AudioLibrary
{
	std::ostream* m_output;
public:
	SDL_AudioLibrary(std::ostream&);
	bool Init();
};