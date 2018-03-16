#pragma once
#include "IComponent.h"
#include "MathHelper.h"
#include <list>
//#include "AnimationSet.h"
//#include "Sprite.h"
#include "SpriteSheet.h"
#include "SDL.h"
#include "UtilMethods.h"

class Entity
{
public:
	Entity( size_t type, float x, float y);
	Entity( size_t type, float x, float y, Sprite *sprite);
	virtual ~Entity();
	virtual void Draw();
	virtual void Update();
	size_t GetType();
	IComponent* GetComponent(size_t type);
	size_t GetId();
	float X;
	float Y;
	bool Active;
	void SetIsDying(bool);
	bool GetIsDying();
//static
	static void RemoveInactiveEntitiesFromList(std::list<Entity*>*entities, bool deleteEntities);
	static void RemoveAllFromList(std::list<Entity*> *entities, bool deleteEntities);
protected:
	size_t m_id;
	size_t m_type;
	std::list<IComponent*> *m_components;
	Sprite *m_sprite;
	bool m_isDying;
	bool m_setActiveToFalse;
};