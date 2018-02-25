
#include "SpriteManager.h"


std::map<std::string, SDL_Texture*> SpriteManager::cache;

void SpriteManager::CleanUp(std::string textureName)
{
	if (cache.count(textureName))
	{
		cleanup(cache[textureName]);
	}
}

SDL_Texture* SpriteManager::GetTexture(std::string textureName)
{
	if (cache.count(textureName))
	{
		return cache[textureName];
	}

	throw "Texture isn't loaded";
}

void SpriteManager::Load(std::string filename, std::string textureName)
{
	if (cache.count(textureName))
	{
		return;
	}

	SDL_Surface* spriteSurface = loadSurface(filename, Globals::Renderer);
	SDL_Texture* spriteSheet;

	if (spriteSurface != nullptr
		&& spriteSurface->format != nullptr
		&& spriteSurface->format->palette != nullptr
		&& spriteSurface->format->palette->colors != nullptr)
	{
		//for transparency, we will grab the [transparentPixelIndex] from the surface we just made
		SDL_Color* transparentPixel = &spriteSurface->format->palette->colors[0];
		SDL_SetColorKey(spriteSurface, 1, SDL_MapRGB(spriteSurface->format, transparentPixel->r, transparentPixel->g, transparentPixel->b));

		spriteSheet = convertSurfaceToTexture(spriteSurface, Globals::Renderer, false);
	}
	else {
		spriteSheet = loadTexture(filename, Globals::Renderer);
	}
	SDL_FreeSurface(spriteSurface);

	cache[textureName] = spriteSheet;
}