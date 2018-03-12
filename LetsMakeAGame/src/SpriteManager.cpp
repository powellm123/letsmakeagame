
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

	////
	//SDL_Surface* surface = loadSurface(std::string(Globals::GetResourcePath() + "title.png"), Globals::Renderer);
	//SDL_Surface* scaledSurface = SDL_CreateRGBSurface(0, Globals::ScreenWidth, Globals::ScreenHeight, 32, 0xFF, 0xFF00, 0xFF0000, 0XFF000000);


	//static SDL_Rect rect;
	//rect.x = 0;
	//rect.y = 0;
	//rect.w = Globals::ScreenWidth;
	//rect.h = Globals::ScreenHeight;
	//int error;
	//if (error = SDL_BlitScaled(surface, NULL, scaledSurface, &rect))
	//{
	//	std::cout << "Error Happened" << std::endl;
	//}

	//testMap = SDL_CreateTextureFromSurface(Globals::Renderer, scaledSurface);
}