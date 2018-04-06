#pragma once

#include "SDL.h"
#include "Globals.h"
#include <vector>

class Sprite
{
public:
	Sprite(SDL_Rect spriteCord, SDL_Texture* texture);
	~Sprite();
	void Draw(SDL_Point loc, float sizeX, float sizeY);
	void Draw(SDL_Point loc, float angle, float sizeX, float sizeY);
	SDL_Rect GetSpritCord() const;
	float GetScale();
private:
	SDL_Rect m_spriteCord;
	SDL_Texture* m_texture;
	float m_scaleToSize;
};

class SpriteSheet
{
public:
	SpriteSheet(SDL_Texture* texture, int width, int height);
	~SpriteSheet();
	void Draw(SDL_Point loc, float sizeX, float sizeY, int index);
	Sprite* GetSprite(int index);
private:
	std::vector<Sprite*> sprites;
	SDL_Texture* m_texture;
};