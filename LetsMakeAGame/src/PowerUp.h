#pragma once

#include "Entity.h"
#include "Sprite.h"
#include "HitBox.h"

class PowerUp : public Entity
{
public:
	static constexpr size_t type = UtilMethods::const_hash("powerup");
	const enum PowerUpType {SpeedUp, ShotUp, ShotCountUp, ExplosionUp};

	static void CreatePowerUp(float x, float y);
	PowerUpType GetPowerUpType() { return m_powerupType; }
protected:
	PowerUp(float x, float y, PowerUpType type, Sprite* sprite);
	PowerUpType m_powerupType;

};

