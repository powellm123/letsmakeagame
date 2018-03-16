
#include "SpriteSheet.h"

Sprite::Sprite(SDL_Rect spriteCord, SDL_Texture * texture) : m_spriteCord(spriteCord), m_texture(texture)
{
}

Sprite::~Sprite()
{
}

void Sprite::Draw(SDL_Point loc, SDL_Point size)
{
	Draw(loc, 0, size);
}

void Sprite::Draw(SDL_Point loc, float angle, SDL_Point size)
{
	SDL_Point center;
	center.x = m_spriteCord.x / 2;
	center.y = m_spriteCord.y / 2;
	SDL_Rect dest; // destination of where we want to draw this frame
	dest.x = loc.x;// -Offset.x - (center.x * scaleX);
	dest.y = loc.y;// -Offset.y - (center.y * scaleY);
	dest.w = m_spriteCord.w * size.x;
	dest.h = m_spriteCord.h * size.y;


	SDL_RenderCopyEx(Globals::Renderer, m_texture, &m_spriteCord, &dest, angle, &center, SDL_RendererFlip::SDL_FLIP_NONE);
}

SpriteSheet::SpriteSheet(SDL_Texture * texture, int width, int height)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect rect;
	rect.w = width;
	rect.h = height;
	for (int i = 0; i < h; i += height)
	{
		rect.y = i;
		for (int j = 0; j < w; j += width)
		{
			rect.x = j;			
			sprites.push_back(new Sprite(rect, texture));
		}
	}
}

SpriteSheet::~SpriteSheet()
{
	for (auto& sprite : sprites)
	{
		delete sprite;
	}
	sprites.clear();

	if (!!m_texture)
		SDL_DestroyTexture(m_texture);
}

void SpriteSheet::Draw(SDL_Point loc, SDL_Point size, int index)
{
	if (index >= sprites.size())
		return;

	sprites[index]->Draw(loc, size);

}


Sprite* SpriteSheet::GetSprite(int index)
{
	if (index >= sprites.size())
		return nullptr;

	return sprites[index];
}