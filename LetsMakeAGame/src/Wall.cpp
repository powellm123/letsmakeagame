
#include "Wall.h"
#include "UtilMethods.h"
#include "SpriteFactory.h"

Wall::Wall(float x, float y) : Entity(type, x, y, SpriteFactory::GetSprite("tile", 1))
{
	m_components->emplace_back(new HitBox(this, 32, 32, true));
}