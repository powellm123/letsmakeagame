
#include "FlameThrower.h"
#include "SpriteFactory.h"

FlameThrower::FlameThrower(float x, float y, float angle) : Bullet(x, y, angle, .1, 1, SpriteFactory::GetSprite("bullet", 3), 80, 4)
{
}

void FlameThrower::Update()
{
	Bullet::Update();
}

void FlameThrower::DyingAction()
{
	if (GetIsDying())
	{
		Active = false;
	}
}
