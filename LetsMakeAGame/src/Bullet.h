#pragma once

#include "SDL.h"
#include "Entity.h"

class Bullet : public Entity
{
public:
	static constexpr size_t type = UtilMethods::const_hash("bullet");
	Bullet( float x, float y, float angle, float lifespan, int size, int moveSpeed=80, int moveLerp=4);
	Bullet(float x, float y, float angle, float lifespan, int size,  Sprite* sprite, int moveSpeed=80, int moveLerp=4);
	virtual ~Bullet();
	void Update() override;
	void Draw() override;
protected:
	virtual void DyingAction();
	float Angle;
	float LifeSpan;
	int m_size;
	static SpriteSheet* bullets;
};