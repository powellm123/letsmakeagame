#pragma once

#include "SDL.h"
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(SDL_Sprite *sprite, float x, float y, float angle);
	~Bullet();
	void Update() override;
	void Draw() override;
protected:
	float Angle;
	float LifeSpan;
};