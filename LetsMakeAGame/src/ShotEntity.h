#pragma once

#include "IComponent.h"
#include "IScene.h"
#include <vector>
#include <list>
#include <SDL.h>
#include "Bullet.h"
#include "Lob_Bullet.h"
#include "Movable.h"
#include "SoundManager.h"
#include "PowerUp.h"
#include "FlameShooter.h"
#include "Mine.h"

class ShotEntity : public IComponent
{
public:
	static constexpr size_t type = UtilMethods::const_hash("shotentity");
	ShotEntity(Entity *actor, SDL_Scancode fireButton, int maxShots);
	void Update() override;
	void AddAltShot(PowerUp::PowerUpType powerupType);
	void IncreaseMaxShot();
	void IncreaseMaxShotCount();
	void IncreateExplosionSize();
	void ShouldPerformFireAction();
	void ShouldPerformAltFireAction();
	void Draw() override;
	PowerUp::PowerUpType GetTopAltFirebulletType();
protected:
	bool m_performFireAction;
	bool m_performAltAction;
	float coolDown;
	int shotcooldownpucount;
	int shotdistpowerupcount;
	int explosionSizeCount;
	float shotdist;
	float shotcooldownMax;
	SDL_Scancode fire;
	int m_maxShots;
	std::list<PowerUp::PowerUpType> m_altfirebullets;
	int m_altfirespot =0;
};