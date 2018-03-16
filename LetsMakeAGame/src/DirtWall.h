#pragma once

#include "Entity.h"
#include "HitBox.h"
#include "Health.h"
#include "PowerUp.h"

class DirtWall : public Entity
{
public:
	static constexpr size_t type = UtilMethods::const_hash("dirtwall");
	DirtWall(float x, float y, Sprite *sprite);
	void Update() override;
};