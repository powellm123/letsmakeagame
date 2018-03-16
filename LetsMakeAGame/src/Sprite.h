#pragma once

//#include "SDL.h"
//#include "SDL_image.h"
//#include "Globals.h"
//#include "SpriteManager.h"
//#include "Helper_Functions.h"
//
//class SDL_Sprite
//{
//	SDL_Sprite(SDL_Rect clip, SDL_Point offset, std::string filename);
//	SDL_Sprite(SDL_Rect clip, SDL_Point offset, SDL_Point size, std::string filename);
//public:
//	SDL_Sprite(SDL_Rect clip, SDL_Point, SDL_Texture *texture);
//	void Draw(SDL_Renderer *renderer, float x, float y, float angle);
//	void Draw2(SDL_Renderer *renderer, float x, float y, float angle, float scaleX, float scaleY);
//	void SetClip(SDL_Rect newclip);
//	void SetOffset(SDL_Point offset);
//
//	static SDL_Sprite* Load(std::string filename, float scale);
//	static SDL_Sprite* Load(int posx, int posy, int w, int h, std::string filename);
//private:
//	std::string m_textureName;
//	SDL_Rect Clip;
//	SDL_Point Offset;
//	SDL_Point Size;
//	SDL_Point center;
//};