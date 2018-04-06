#include "DirtWall.h"
#include "SpriteFactory.h"

DirtWall::DirtWall(float x, float y) : Entity(type, x, y, SpriteFactory::GetSprite("tile", 0))
{
	m_components->emplace_back(new HitBox(this, 32, 32, true));
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
