#pragma once

#include "IComponent.h"
#include "IScene.h"
#include <list>
#include <SDL.h>
#include "Bullet.h"
#include "Lob_Bullet.h"
#include "Movable.h"

class ShotEntity : public IComponent
{
public:
	static constexpr size_t type = UtilMethods::const_hash("shotentity");
	ShotEntity(Entity *actor, SDL_Scancode fireButton, int maxShots);
	void Update() override;
	void IncreaseMaxShot();
	void IncreaseMaxShotCount();
	void IncreateExplosionSize();
	void ShouldPerformFireAction();
	void ShouldPerformAltFireAction();
	void Draw() override;
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
};