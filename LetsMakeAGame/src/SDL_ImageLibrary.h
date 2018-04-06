#pragma once

#include <ostream>
#include "SDL_image.h"

class SDL_ImageLibrary
{
	std::ostream* m_output;
public:
	SDL_ImageLibrary(std::ostream&);
	SDL_Texture* Load(const std::string &file, SDL_Renderer *ren);
	bool Init();
};