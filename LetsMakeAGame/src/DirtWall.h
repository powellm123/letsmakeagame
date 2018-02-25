#pragma once

#include "Entity.h"
#include "HitBox.h"
#include "Health.h"

class DirtWall : public Entity
{
public:
	DirtWall(float x, float y, SDL_Sprite *sprite);
};