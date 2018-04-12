
#include "SpriteFactory.h"
#include "Helper_Functions.h"


std::map< unsigned, SpriteSheet*> SpriteFactory::_cache;

void SpriteFactory::AddSpriteSheet(std::string filename, std::string name, int width, int height)
{
	unsigned hash = std::hash<std::string>{}(name);
	if (_cache.count(hash))
	{
		return;
	}

	SDL_Surface* spriteSurface = loadSurface(Globals::GetResourcePath() + filename, Globals::Renderer);
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
	else 
	{
		spriteSheet = loadTexture(Globals::GetResourcePath() + filename, Globals::Renderer);
	}
	SDL_FreeSurface(spriteSurface);

	_cache[hash] = new SpriteSheet(spriteSheet, width, height);
}

Sprite* SpriteFactory::GetSprite(std::string name, int index)
{
	unsigned hash = std::hash<std::string>{}(name);
	if(_cache.count(hash))
		return _cache[hash]->GetSprite(index);

	return nullptr;
}

Animation * SpriteFactory::GetAnimation(std::string name, int index, int frames)
{
	unsigned hash = std::hash<std::string>{}(name);
	if (_cache.count(hash))
		return _cache[hash]->GetAnimation(index, frames);

	return nullptr;
}
