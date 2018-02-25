#pragma once
#include <string>
#include <map>
#include "Globals.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Helper_Functions.h"

class SpriteManager
{
public:
	static void CleanUp(std::string textureName);
	static SDL_Texture* GetTexture(std::string textureName);
	static void Load(std::string filename, std::string textureName);

private:
	static std::map<std::string, SDL_Texture*> cache;

};
