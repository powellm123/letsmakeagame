#pragma once

#include "Entity.h"
#include "HitBox.h"
#include "TimeController.h"

class Explosion : public Entity
{
public:
	static constexpr size_t type = UtilMethods::const_hash("explosion");	
	Explosion(float x, float y, int size);
	void Update() override;
	void Draw() override;
private:
	float LifeSpan;
	float m_size;
	static SpriteSheet* explosions;
};
