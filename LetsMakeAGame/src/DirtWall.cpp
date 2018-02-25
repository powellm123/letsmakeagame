#include "DirtWall.h"

DirtWall::DirtWall(float x, float y, SDL_Sprite *sprite) : Entity("dirtwall", x, y, sprite)
{
	m_components->emplace_back(new HitBox(this, 32, 32, -16, true));
	m_components->emplace_back(new HealthComponent(this, 1));
}
