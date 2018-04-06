#pragma once

#include <ostream>
#include "SDL_ttf.h"

class SDL_TextToFontLibrary
{
	std::ostream* m_output;
public:
	SDL_TextToFontLibrary(std::ostream&);
	bool Init();
};