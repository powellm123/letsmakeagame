#pragma once
#include "SDL.h"
#include "IScene.h"
#include "Helper_Functions.h"
#include "Globals.h"
#include "Player.h"
#include "PowerUp.h"
#include "Wall.h"
#include "DirtWall.h"


class TestScene : public IScene
{
public:
	TestScene();
	~TestScene();
	void Update() override;
	void Draw() override;

private:
	SDL_Texture * testMap;

};