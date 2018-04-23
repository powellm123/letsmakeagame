#pragma once

#include "Entity.h"
#include "Player.h"
#include "SpriteObjects.h"

class HealthBar : public SpriteObjects
{
	float posX;
	float posY;
public:
	HealthBar(Player* actor, float x, float y);
	virtual ~HealthBar();
	void Draw() override;
	
private:
	Player * m_actor;
	Sprite* healthbarcolor;
	Sprite* border[9];
	Sprite* itemPickups[3];

};