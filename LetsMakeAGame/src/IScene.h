#pragma once

#include <list>
#include "Entity.h"

class IScene
{
public:
	IScene();
	~IScene();
	virtual void Update();
	virtual void Draw();
	static std::list<Entity*>* m_entities;
protected:
};