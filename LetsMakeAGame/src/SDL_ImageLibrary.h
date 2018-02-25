#pragma once

#include "GraphicsLibrary.h"
#include <ostream>
#include "SDL_image.h"

class SDL_ImageLibrary : public IImageGraphics<SDL_Renderer, SDL_Texture>
{
	std::ostream* m_output;
public:
	SDL_ImageLibrary(std::ostream&);
	SDL_Texture* Load(const std::string &file, SDL_Renderer *ren) override;
	bool Init() override;
};