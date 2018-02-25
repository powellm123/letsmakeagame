#pragma once

#include "GraphicsLibrary.h"
#include <ostream>
#include "SDL_ttf.h"

class SDL_TextToFontLibrary : public ITextToFontLibrary
{
	std::ostream* m_output;
public:
	SDL_TextToFontLibrary(std::ostream&);
	bool Init() override;
};