#pragma once

#include <list>
#include "Entity.h"
#include "Player.h"
#include "SpriteObjects.h"
#include "MusicPlayer.h"
#include "IMenu.h"

class IScene
{
public:
	IScene();
	~IScene();
	virtual void Init() = 0;
	virtual void Update();
	virtual void Draw();
	static std::list<Entity*> GetEntiries(size_t type);
	int GetAliveCount();
	static std::list<IMenu*> * m_menus;
	static std::list<Entity*>* m_entities;
	static std::list<SpriteObjects*> * m_spriteobjects;
	static void RemoveInactiveSpriteObjects();
	static SDL_Texture* GetTexture(std::string name);
protected:
};