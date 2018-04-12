#pragma once

#include <list>
#include "Player.h"
#include "ControllerGather.h"

struct Level
{
	std::list<Player*> players;
	std::string mapname;
	int humanPlayers;
	int cpuPlayers;
	std::map<int, SDL_JoystickID> joysticks;
	std::vector<int> color;
};

class LevelCreator
{
	LevelCreator();
	Level m_level;
public:
	LevelCreator * AddPlayer(Player* player);
	LevelCreator * AddHumanPlayer(int count);
	LevelCreator * AddCpuPlayer(int count);
	LevelCreator * RemovePlayer(Player* player);
	LevelCreator * SetLevelSkin(std::string mapname);
	LevelCreator * AddControllers(std::list<PlayerInput> playerinputs);
	
	Level BuildLevel();

	static LevelCreator Instance;
};