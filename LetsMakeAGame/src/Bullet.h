#pragma once

#include "SDL.h"
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(float x, float y, float angle, float lifespan);
	~Bullet();
	void Update() override;
	void Draw() override;
protected:
	Bullet(SDL_Sprite *sprite, float x, float y, float angle, float lifespan);
	float Angle;
	float LifeSpan;
};