#pragma once

#include "Bullet.h"
#include "TimeController.h"
#include "Entity.h"
#include "Movable.h"

class Lob_Bullet : public Bullet
{
public:
	Lob_Bullet(float x, float y, float angle);
	void Update() override;

protected:
	float Z;
	float Z_volicity;
	float Z_acc;
};