#pragma once
#include <string>
#include "UtilMethods.h"

class Entity;

class IComponent
{
public:
	IComponent(Entity *actor, std::string name, size_t type) : m_actor(actor), m_name(name), m_type(type) {}
	virtual ~IComponent() {}
	virtual void Update() = 0;
	virtual void Draw() = 0;
	std::string GetName();
	size_t GetType();
protected:
	Entity *m_actor;
	std::string m_name;
	size_t m_type;
};