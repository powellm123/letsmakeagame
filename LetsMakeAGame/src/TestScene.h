#pragma once
#include <sstream>
#include "SDL.h"
#include "IScene.h"
#include "Helper_Functions.h"
#include "Globals.h"
#include "Tank.h"
#include "CpuTank.h"
#include "TankControlledTank.h"
#include "PowerUp.h"
#include "Wall.h"
#include "DirtWall.h"
#include "SceneManager.h"
#include "Map.h"

class TestScene : public IScene
{
	const int width = Globals::ScreenWidth / 32;
	const int height = Globals::ScreenHeight / 32;
public:
	TestScene();
	~TestScene();
	void Init() override;
	void Update() override;
	void Draw() override;

private:
	Map *map;
	Menu * m_menu1;
	SpriteSheet* TileSet;
	SpriteSheet* PowerUps;
	SpriteSheet* Tanks;
	SDL_Texture * testMap;
	SDL_Texture * gameOverTexture;
	SDL_Texture * text;
	bool m_matchend;
	float matchendTimer;
};