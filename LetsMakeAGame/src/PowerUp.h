#pragma once

#include "Entity.h"
#include "Sprite.h"
#include "HitBox.h"

class PowerUp : public Entity
{
public:
	const enum PowerUpType {SpeedUp, ShotUp, ShotCountUp};

	static void CreatePowerUp(float x, float y);
	PowerUpType GetPowerUpType() { return m_powerupType; }
protected:
	PowerUp(float x, float y, PowerUpType type, SDL_Sprite* sprite);
	PowerUpType m_powerupType;
};

