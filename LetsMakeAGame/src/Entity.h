#pragma once
#include "IComponent.h"
#include <list>
//#include "AnimationSet.h"
#include "Sprite.h"
#include "SDL.h"
#include "UtilMethods.h"

class Entity
{
public:
	Entity( std::string type, float x, float y);
	Entity( std::string type, float x, float y, SDL_Sprite *sprite);
	~Entity();
	virtual void Draw();
	virtual void Update();
	std::string GetType();
	IComponent* GetComponent(std::string name);
	std::string GetId();
	float X;
	float Y;
	bool Active;
	void SetIsDying(bool);
	bool GetIsDying();
//static
	static void RemoveInactiveEntitiesFromList(std::list<Entity*>*entities, bool deleteEntities);
	static void RemoveAllFromList(list<Entity*> *entities, bool deleteEntities);
protected:
	std::string m_id;
	std::string m_type;
	std::list<IComponent*> *m_components;
	//AnimationSet *m_animationSet;
	SDL_Sprite *m_sprite;
	bool m_isDying;
};