#pragma once
#include <string>
#include <map>
#include <list>
#include "Globals.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Helper_Functions.h"
#include "SpriteSheet.h";

class SpriteManager
{
public:
	static void CleanUp(std::string textureName);
	static SDL_Texture* GetTexture(std::string textureName);
	static void Load(std::string filename, std::string textureName);
	static SpriteSheet* LoadTileSet(std::string filename, int width, int height);
private:
	static std::map<std::string, SDL_Texture*> cache;

};
