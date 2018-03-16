
#include "TankControlledTank.h"


TankControlledTank::TankControlledTank(float x, float y, int playernumber, Buttons * buttons, Sprite * sprite)
	: Tank(x, y, playernumber, buttons, sprite)
{
	m_rotateLerp = 3;
	m_relativeAngle = 0;
}

void TankControlledTank::PerformMove(float angle, float value)
{
	Movable* comp = (Movable*)GetComponent(Movable::type);
	m_relativeAngle = comp->GetAngle();
	float newangle = angle;

	float power = 0;
	if (newangle > 180 && newangle <= 360) // 270)
	{
		power = .9999;
	}
	if (newangle > 0 && angle < 180) // 90)
	{
		power = -.9999;
	}

	if (newangle > 90 && newangle < 270)
	{
		float rotate = 50;
		m_relativeAngle -= rotate * TimeController::instance.DeltaTime * m_rotateLerp;
	}
	else if(newangle > 270 || newangle < 90)
	{
		float rotate = 50;
		m_relativeAngle += rotate * TimeController::instance.DeltaTime * m_rotateLerp;
	}

	Tank::PerformMove(m_relativeAngle, power);
}
