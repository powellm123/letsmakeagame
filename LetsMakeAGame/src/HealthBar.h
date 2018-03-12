#pragma once

#include "Entity.h"
#include "Player.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "SpriteObjects.h"

class HealthBar : public SpriteObjects
{
public:
	HealthBar(Player* actor, float x, float y);
	void Draw() override;

private:
	Player * m_actor;
	SDL_Sprite* healthbarcolor;
	SDL_Sprite* border;

	float posX;
	float posY;
};