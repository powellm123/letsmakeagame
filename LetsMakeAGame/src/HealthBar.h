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
	virtual ~HealthBar();
	void Draw() override;

private:
	Player * m_actor;
	Sprite* healthbarcolor;
	Sprite* border;

	float posX;
	float posY;
};