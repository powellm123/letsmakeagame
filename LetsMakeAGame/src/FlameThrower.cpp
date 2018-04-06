
#include "FlameThrower.h"
#include "SpriteFactory.h"

FlameThrower::FlameThrower(float x, float y, float angle) : Bullet(x, y, angle, 30, 2, SpriteFactory::GetSprite("bullet", 3), 4, 0)
{
}

void FlameThrower::Update()
{
	Bullet::Update();
}

void FlameThrower::DyingAction()
{
}
