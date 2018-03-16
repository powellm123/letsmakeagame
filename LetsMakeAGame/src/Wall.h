#pragma once

#include "Entity.h"
#include "Sprite.h"
#include "HitBox.h"
#include "UtilMethods.h"

class Wall : public Entity
{
public:
	static constexpr size_t type = UtilMethods::const_hash("wall");
	Wall(float x, float y, Sprite *sprite);
};

