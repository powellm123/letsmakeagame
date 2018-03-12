
#include "TankControlledTank.h"


TankControlledTank::TankControlledTank(float x, float y, int playernumber, Buttons * buttons, SDL_Sprite * sprite)
	: Tank(x, y, playernumber, buttons, sprite)
{
	m_rotateLerp = 2;
	m_relativeAngle = 0;
}

void TankControlledTank::PerformMove(float angle, float value)
{
	Movable* comp = (Movable*)GetComponent("movable");
	m_relativeAngle = comp->GetAngle();
	float newangle = angle;

	float power = 0;
	if (newangle >= 180)
	{
		float rotate = newangle - 270;
		m_relativeAngle += rotate * TimeController::instance.DeltaTime * m_rotateLerp;

		power = 2 * (newangle- 180) / 270.0;
	}
	else if (newangle >= 0)
	{
		float rotate = newangle - 90;
		m_relativeAngle -= rotate * TimeController::instance.DeltaTime * m_rotateLerp;

		power = -2 * newangle/90.0;
	}

	Tank::PerformMove(m_relativeAngle, power);
}
