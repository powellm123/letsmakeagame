#pragma once

#include "IMenu.h"
#include "UtilMethods.h"
#include <sstream>
#include "LevelCreator.h"
#include "SceneManager.h"
#include "BattleScene.h"

class LevelSelectMenu : public IMenu
{
	SDL_Texture *m_levelMap;
	SDL_Texture *m_levelName;
	SDL_Texture* helpMessage;
	int m_levelIndex;
	std::map<int, std::pair<std::string, std::string>> levels;
public:
	static constexpr unsigned MenuId = UtilMethods::const_hash("BattleOptionsMenu");
	LevelSelectMenu();
	SDL_Texture* LoadImage(int index);
	void Increase();
	void Decrease();
	void Update() override;
	void Draw() override;
};