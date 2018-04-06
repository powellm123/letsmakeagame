#pragma once

#include "Bullet.h"

class FlameThrower : public Bullet
{
	float startx, starty;
	int dist;
public:
	FlameThrower(float x, float y, float angle);
	void Update() override;
protected:
	void DyingAction() override;
};