
#include "Wall.h"
#include "UtilMethods.h"

Wall::Wall(float x, float y, Sprite *sprite) : Entity(type, x, y, sprite)
{
	m_components->emplace_back(new HitBox(this, 32, 32, -16, true));
}