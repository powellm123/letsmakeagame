#pragma once

#include "IComponent.h"
#include "FlameThrower.h"
#include "IScene.h"
#include "Movable.h"

class FlameShooter : public IComponent
{
	float m_shottime;
	float m_nextshot;
	float m_maxshottimes=1.5;
public:
	static constexpr size_t type = UtilMethods::const_hash("FlameShooter");
	FlameShooter(Entity* actor);
	void ShotFire();
	void Update() override;
	void Draw() override;
};