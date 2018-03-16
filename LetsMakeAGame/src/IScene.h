#pragma once

#include <list>
#include "Entity.h"
#include "Player.h"
#include "SpriteObjects.h"

class IScene
{
public:
	IScene();
	~IScene();
	virtual void Init() = 0;
	virtual void Update();
	virtual void Draw();
	std::list<Entity*> GetEntiries(size_t type);
	int GetAliveCount();
	static std::list<Entity*>* m_entities;
	static std::list<SpriteObjects*> * m_spriteobjects;
protected:
};