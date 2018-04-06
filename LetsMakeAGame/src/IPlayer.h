#pragma once

#include "Entity.h"
#include <list>

class IPlayer : public Entity
{
public:
	const enum class Action { Up, Down, Left, Right, Fire, AltFire, Pause };
	IPlayer(size_t type, float x, float y): Entity(type, x, y){}
	IPlayer(size_t type, float x, float y, Sprite *sprite) :Entity(type, x, y, sprite){}

protected:
	std::list<Action> m_actions;
};