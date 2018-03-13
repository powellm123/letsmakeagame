#pragma once

#include "Entity.h"
#include "HitBox.h"
#include "Sprite.h"

class Boarder : public Entity
{
	int m_width;
	int m_height;
public:
	Boarder(float x, float y, int width, int height) : Entity("boarder", x, y, SDL_Sprite::Load("wall.png", 1)), m_width(width/32), m_height(height/32)
	{
		m_components->emplace_back(new HitBox(this, width, height, -16, true));
	}

	void Draw() override
	{
		if (m_sprite != nullptr)
			m_sprite->Draw2(Globals::Renderer, X, Y, 0, m_width, m_height);
		for (auto& component : *m_components)
		{
			component->Draw();
		}
	}
};