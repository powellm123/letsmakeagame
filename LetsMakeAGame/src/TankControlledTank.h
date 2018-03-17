#pragma once


#include "Tank.h"

class TankControlledTank : public Tank
{
public:
	TankControlledTank(float x, float y, int playernumber, Buttons *buttons);
	void PerformMove(float angle, float value) override;

private:
	float m_relativeAngle;
	float m_rotateLerp;
};