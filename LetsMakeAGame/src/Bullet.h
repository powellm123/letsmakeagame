#pragma once

#include "SDL.h"
#include "Entity.h"

class Bullet : public Entity
{
public:
	static constexpr size_t type = UtilMethods::const_hash("bullet");
	Bullet( float x, float y, float angle, float lifespan, int size);
	Bullet(float x, float y, float angle, float lifespan, int size, Sprite* sprite);
	virtual ~Bullet();
	void Update() override;
	void Draw() override;
protected:
	float Angle;
	float LifeSpan;
	int m_size;
	static SpriteSheet* bullets;
};