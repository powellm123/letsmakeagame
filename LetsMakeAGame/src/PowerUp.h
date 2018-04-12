#pragma once

#include "Entity.h"
#include "HitBox.h"

class PowerUp : public Entity
{
public:
	static constexpr size_t type = UtilMethods::const_hash("powerup");
	const enum PowerUpType {SpeedUp, ShotUp, ShotCountUp, ExplosionUp, CannonBall, FlameThrower, Mine};

	static void CreatePowerUp(float x, float y);
	PowerUpType GetPowerUpType() { return m_powerupType; }
	void Update() override;
protected:
	PowerUp(float x, float y, PowerUpType type, Sprite* sprite);
	PowerUpType m_powerupType;

};

