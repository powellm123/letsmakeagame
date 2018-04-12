
#include "SpriteSheet.h"
#include "MathHelper.h"

Sprite::Sprite(SDL_Rect spriteCord, SDL_Texture * texture) : m_spriteCord(spriteCord), m_texture(texture), m_scaleToSize(Globals::TileWidth/(float)spriteCord.w)
{
}

Sprite::~Sprite()
{
}

void Sprite::Draw(SDL_Point loc, float sizeX, float sizeY)
{
	Draw(loc, 0, sizeX, sizeY);
}

void Sprite::Draw(SDL_Point loc, float angle, float sizeX, float sizeY)
{
	SDL_Point center;
	center.x = m_scaleToSize * m_spriteCord.w / 2;
	center.y = m_scaleToSize * m_spriteCord.h / 2;
	SDL_Rect dest; // destination of where we want to draw this frame
	dest.x = loc.x;// -center.x; // m_scaleToSize * m_spriteCord.w / 2;
	dest.y = loc.y;// -center.y; // m_scaleToSize * m_spriteCord.h / 2;
	dest.w = m_scaleToSize * m_spriteCord.w * sizeX;
	dest.h = m_scaleToSize * m_spriteCord.h * sizeY;


	SDL_RenderCopyEx(Globals::Renderer, m_texture, &m_spriteCord, &dest, angle, &center, SDL_RendererFlip::SDL_FLIP_NONE);
}

SDL_Rect Sprite::GetSpritCord() const
{
	return m_spriteCord;
}

float Sprite::GetScale()
{
	return m_scaleToSize;
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

void SpriteSheet::Draw(SDL_Point loc, float sizeX, float sizeY, int index)
{
	if (index >= sprites.size())
		return;

	sprites[index]->Draw(loc, sizeX, sizeY);

}


Sprite* SpriteSheet::GetSprite(int index)
{
	if (index >= sprites.size())
		return nullptr;

	return sprites[index];
}

Animation* SpriteSheet::GetAnimation(int index, int frames)
{
	if (index + frames > sprites.size())
	{
		return nullptr;
	}

	std::vector<Sprite*> sprite;
	for (int i = index; i < index + frames; i++)
	{
		sprite.push_back(sprites[i]);
	}

	return new Animation(sprite);
}


Animation::Animation(std::vector<Sprite*> sprites) : m_sprites(sprites)
{
	m_frames = 0;
	m_maxFrames = sprites.size();
	m_framelength = m_lengthFrameMax = .12;
}

Animation::~Animation()
{
	m_sprites.clear();
}

void Animation::Update()
{
	if (m_framelength < 0)
	{
		m_frames++;
		m_frames %= m_maxFrames;
		m_framelength = m_lengthFrameMax;
	}

	m_framelength -= TimeController::instance.DeltaTime;
}

void Animation::Draw(SDL_Point loc, float sizeX, float sizeY)
{
	m_sprites[m_frames]->Draw(loc, sizeX, sizeY);
}

SDL_Rect Animation::GetSpritCord() const
{
	return m_sprites[m_frames]->GetSpritCord();
}

float Animation::GetScale()
{
	return m_sprites[m_frames]->GetScale();
}
