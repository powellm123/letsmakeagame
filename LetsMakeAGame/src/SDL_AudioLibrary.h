#pragma once

#include "GraphicsLibrary.h"
#include <ostream>
#include "SDL_mixer.h"

class SDL_AudioLibrary : public IAudioLibrary
{
	std::ostream* m_output;
public:
	SDL_AudioLibrary(std::ostream&);
	bool Init() override;
};