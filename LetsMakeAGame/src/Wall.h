#pragma once

#include "Entity.h"
#include "Sprite.h"
#include "HitBox.h"

class Wall : public Entity
{
public:
	Wall(float x, float y, SDL_Sprite *sprite) : Entity("wall", x, y, sprite)
	{
		m_components->emplace_back(new HitBox(this, 32, 32, -16, true));
	}
};