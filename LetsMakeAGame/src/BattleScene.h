#pragma once

#include "Map.h"
#include "IScene.h"
#include "LevelCreator.h"

class BattleScene : public IScene
{
	std::map<int, std::pair<int, int>> startlocations;
	const int width = Globals::ScreenWidth / Globals::TileWidth;
	const int height = Globals::ScreenHeight / Globals::TileHeight;
	float m_timebeforestart;
	Level m_level;
	unsigned songid;
	bool isplaying;
public:
	static constexpr size_t SCENE = UtilMethods::const_hash("battlescene");
	BattleScene();
	~BattleScene();
	void Init() override;
	void Update() override;
	void Draw() override;

private:
	Map * map;
	SDL_Texture * loading;
	SDL_Texture * testMap;
	SDL_Texture * gameOverTexture;
	SDL_Texture * text;
	SDL_Texture * getReady;
	SDL_Texture * start;
	bool m_matchend;
	float matchendTimer;
};