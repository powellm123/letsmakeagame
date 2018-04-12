#pragma once

#include "Bullet.h"
#include "SpriteFactory.h"

class Mine : public Bullet
{
public:
	Mine(float x, float y, float angle) : Bullet(x, y, angle, 9999, 2, SpriteFactory::GetSprite("bullet", 2), 0, 0)
	{
	}
};