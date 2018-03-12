#pragma once

#include "Entity.h"
#include "Sprite.h"
#include "HitBox.h"

class PowerUp : public Entity
{
public:
	const enum PowerUpType {SpeedUp, ShotUp, ShotCountUp};
	PowerUp(float x, float y, PowerUpType type, SDL_Sprite* sprite) : Entity("powerup", x, y,sprite )
	{
		m_components->emplace_back(new HitBox(this, 32, 32, -16, true));
		m_powerupType = type;
	}

	PowerUpType GetPowerUpType() { return m_powerupType; }
protected:
	PowerUpType m_powerupType;
};