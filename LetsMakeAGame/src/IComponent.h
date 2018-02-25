#pragma once
#include <string>

class Entity;

class IComponent
{
public:
	IComponent(Entity *actor, std::string name) : m_actor(actor), m_name(name) {}
	virtual void Update() = 0;
	virtual void Draw() = 0;
	std::string GetName();
protected:
	Entity *m_actor;
	std::string m_name;
};