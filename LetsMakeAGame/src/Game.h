#pragma once
#include <list>
#include "GraphicsLibrary.h"
#include "SDL_GraphicsLibrary.h"
#include "IScene.h"
#include "Entity.h"
#include "Globals.h"
#include "Controller.h"
#include "SceneManager.h"

class Game
{
public:
	Game(SDL_GraphicsLibrary *gl);
	~Game();
	void Run();
	void Draw();
	void Update();
	static int Width;
	static int Height;
	static int WidthHalf;
	static int HeightHalf;
private:
	SDL_GraphicsLibrary *m_gl;
	std::list<Entity*> *m_entity;
};