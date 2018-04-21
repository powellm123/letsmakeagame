#include "LevelCreator.h"

LevelCreator LevelCreator::Instance;

LevelCreator::LevelCreator()
{
}

LevelCreator * LevelCreator::AddPlayer(Player * player)
{
	m_level.players.push_back(player);
	return this;
}

LevelCreator * LevelCreator::AddHumanPlayer(int count)
{
	m_level.humanPlayers = count;
	return this;
}

LevelCreator * LevelCreator::AddTankChoose(std::vector<PlayerTankChoose> ptc)
{
	m_level.playerTankChoose = ptc;
	return this;
}

LevelCreator * LevelCreator::AddCpuPlayer(int count)
{
	m_level.cpuPlayers = count;
	return this;
}

LevelCreator * LevelCreator::RemovePlayer(Player * player)
{
	m_level.players.remove(player);
	return this;
}

LevelCreator * LevelCreator::SetLevelSkin(std::string mapname)
{
	m_level.mapname = mapname;
	return this;
}

LevelCreator * LevelCreator::AddControllers(std::list<PlayerInput> playerinputs)
{
	for (auto playerinput : playerinputs)
	{
		m_level.joysticks[playerinput.playerSpot-1] = (playerinput.joystickId);
	}
	return this;
}

Level LevelCreator::BuildLevel()
{
	return m_level;
}
