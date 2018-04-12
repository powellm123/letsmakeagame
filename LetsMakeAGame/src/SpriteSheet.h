#pragma once

#include "SDL.h"
#include "Globals.h"
#include <vector>
#include "TimeController.h"

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


class Animation
{
public:
	Animation(std::vector<Sprite*> sprites);
	~Animation();
	void Update();
	void Draw(SDL_Point loc, float sizeX, float sizeY);
	SDL_Rect GetSpritCord() const;
	float GetScale();
private:
	SDL_Rect m_spriteCord;
	SDL_Texture* m_texture;
	float m_scaleToSize;
	int m_frames;
	int m_maxFrames;
	float m_framelength = .12;
	float m_lengthFrameMax = .12;
	std::vector<Sprite*> m_sprites;
};

class SpriteSheet
{
public:
	SpriteSheet(SDL_Texture* texture, int width, int height);
	~SpriteSheet();
	void Draw(SDL_Point loc, float sizeX, float sizeY, int index);
	Sprite* GetSprite(int index);
	Animation* GetAnimation(int index, int frames);
private:
	std::vector<Sprite*> sprites;
	SDL_Texture* m_texture;
};