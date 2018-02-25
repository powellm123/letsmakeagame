#pragma once
#include <list>
#include "GraphicsLibrary.h"
#include "SDL_GraphicsLibrary.h"
#include "IScene.h"
#include "Entity.h"
#include "TestScene.h"
#include "Globals.h"
#include "Controller.h"

class Game
{
public:
	Game(SDL_GraphicsLibrary *gl);
	~Game();
	void Run();
	void Draw();
	void Update();
private:
	IScene *m_scene;
	SDL_GraphicsLibrary *m_gl;
	std::list<Entity*> *m_entity;
};