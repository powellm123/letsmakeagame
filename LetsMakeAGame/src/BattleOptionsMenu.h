#pragma once

#include "SDL.h"
#include "IMenu.h"
#include "UtilMethods.h"
#include "LevelSelectMenu.h"
#include <sstream>

class BattleOptionsMenu : public IMenu
{
private:
	int m_cpus = 0;
	int m_hits = 3;
	int m_playerCount;
	SDL_Texture* cpuCountTexture;
	SDL_Texture* hitCountTexture;
	SDL_Texture* helpMessage;
public:
	static constexpr unsigned MenuId = UtilMethods::const_hash("BattleOptionsMenu");
	BattleOptionsMenu(int playerCount);
	void Increase();
	void Decrease();
	void Update() override;
	void Draw() override;
};