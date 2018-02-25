#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Globals.h"
#include "SpriteManager.h"
#include "Helper_Functions.h"

class SDL_Sprite
{
public:
	SDL_Sprite(SDL_Rect clip, SDL_Point offset, std::string filename) : Clip(clip), Offset(offset), m_textureName(filename)
	{
		SpriteManager::Load(Globals::GetResourcePath() + filename, filename);
	}


	void Draw(SDL_Renderer *renderer, float x, float y, float angle)
	{

		SDL_Point center;
		center.x = Clip.x + Clip.w / 2;
		center.y = Clip.y + Clip.h / 2;


		SDL_Rect dest; // destination of where we want to draw this frame
		dest.x = x - Offset.x - center.x;
		dest.y = y - Offset.y - center.y;
		dest.w = Clip.w;
		dest.h = Clip.h;

		SDL_Texture* spriteSheet = SpriteManager::GetTexture(m_textureName);

		SDL_RenderCopyEx(renderer, spriteSheet, &Clip, &dest, angle, &center, SDL_RendererFlip::SDL_FLIP_NONE);
	}

	static SDL_Sprite* Load(int posx, int posy, int w, int h, std::string filename)
	{
		SDL_Rect dest;
		dest.x = 0;
		dest.y = 0;
		dest.w = w;
		dest.h = h;
		SDL_Point point;
		point.x = posx;
		point.y = posy;
		return new SDL_Sprite(dest, point, filename);
	}
private:
	std::string m_textureName;
	SDL_Rect Clip;
	SDL_Point Offset;
};