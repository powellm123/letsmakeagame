//
//#include "Sprite.h"
//
//SDL_Sprite::SDL_Sprite(SDL_Rect clip, SDL_Point offset, std::string filename) : Clip(clip), Offset(offset), m_textureName(filename)
//{
//	SpriteManager::Load(Globals::GetResourcePath() + filename, filename);
//
//	center.x = Clip.x + Clip.w / 2;
//	center.y = Clip.y + Clip.h / 2;
//	Size.x = Clip.w;
//	Size.y = Clip.h;
//}
//
//SDL_Sprite::SDL_Sprite(SDL_Rect clip, SDL_Point offset, SDL_Point size, std::string filename) : Clip(clip), Offset(offset), m_textureName(filename), Size(size)
//{
//	SpriteManager::Load(Globals::GetResourcePath() + filename, filename);
//
//	center.x = Clip.x + Clip.w / 2;
//	center.y = Clip.y + Clip.h / 2;
//}
//
//SDL_Sprite(SDL_Rect clip, SDL_Point, SDL_Texture *texture)
//{
//
//}
//
//
//void SDL_Sprite::Draw(SDL_Renderer *renderer, float x, float y, float angle)
//{
//	SDL_Rect dest; // destination of where we want to draw this frame
//	dest.x = x - Offset.x - center.x;
//	dest.y = y - Offset.y - center.y;
//	dest.w = Clip.w;
//	dest.h = Clip.h;
//
//	SDL_Texture* spriteSheet = SpriteManager::GetTexture(m_textureName);
//
//	SDL_RenderCopyEx(renderer, spriteSheet, &Clip, &dest, angle, &center, SDL_RendererFlip::SDL_FLIP_NONE);
//}
//
//void SDL_Sprite::Draw2(SDL_Renderer *renderer, float x, float y, float angle, float scaleX, float scaleY)
//{
//	SDL_Rect dest; // destination of where we want to draw this frame
//	dest.x = x - Offset.x - (center.x * scaleX);
//	dest.y = y - Offset.y - (center.y * scaleY);
//	dest.w = Size.x * scaleX;
//	dest.h = Size.y * scaleY;
//
//	SDL_Texture* spriteSheet = SpriteManager::GetTexture(m_textureName);
//
//	SDL_RenderCopyEx(renderer, spriteSheet, &Clip, &dest, angle, &center, SDL_RendererFlip::SDL_FLIP_NONE);
//}
//
//void SDL_Sprite::SetClip(SDL_Rect newclip)
//{
//	Clip = newclip;
//
//	center.x = Clip.x + Clip.w / 2;
//	center.y = Clip.y + Clip.h / 2;
//}
//void SDL_Sprite::SetOffset(SDL_Point offset)
//{
//	Offset = offset;
//}
//SDL_Sprite* SDL_Sprite::Load(std::string filename, float scale)
//{
//	SDL_Rect rect;
//	SDL_Point point;
//
//	SDL_Sprite* sprite = new SDL_Sprite(SDL_Rect(), SDL_Point(), filename);
//	int w, h;
//	SDL_QueryTexture(SpriteManager::GetTexture(sprite->m_textureName), NULL, NULL, &w, &h);
//	rect.x = 0;
//	rect.y = 0;
//	rect.w = w;
//	rect.h = h;
//	sprite->Clip = rect;
//	sprite->Offset.x = 0;
//	sprite->Offset.y = 0;
//	sprite->Size.x = w * scale;
//	sprite->Size.y = h * scale;
//	sprite->center.x = rect.x + rect.w / 2;
//	sprite->center.y = rect.y + rect.h / 2;
//	return sprite;
//}
//
//SDL_Sprite* SDL_Sprite::Load(int posx, int posy, int w, int h, std::string filename)
//{
//	SDL_Rect dest;
//	dest.x = 0;
//	dest.y = 0;
//	dest.w = w;
//	dest.h = h;
//	SDL_Point point;
//	point.x = posx;
//	point.y = posy;
//	return new SDL_Sprite(dest, point, filename);
//}