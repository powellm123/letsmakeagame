#include "DirtWall.h"

DirtWall::DirtWall(float x, float y, Sprite *sprite) : Entity(type, x, y, sprite)
{
	m_components->emplace_back(new HitBox(this, 32, 32, -16, true));
	m_components->emplace_back(new HealthComponent(this, 1));
}

void DirtWall::Update()
{
	Entity::Update();

	if (GetIsDying())
	{
		if(rand() % 5 < 3)
			PowerUp::CreatePowerUp(X, Y);
		Active = false;
	}
}
