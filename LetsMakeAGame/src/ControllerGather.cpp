#include "ControllerGather.h"
#include "Inputtracker.h"
#include "Helper_Functions.h"
#include "BattleOptionsMenu.h"
#include <sstream>

ControllerGather::ControllerGather() : IPlayer(type, 0, 0)
{
	InputTracker::SubscribeControllerGather(this);

	//generate score text
	SDL_Color color = { 255, 255, 255, 255 };
	std::stringstream ss;
	ss << "Ready";

	readyText = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 120, Globals::Renderer);
}

ControllerGather::~ControllerGather()
{
	for (auto player : players)
	{
		delete player;
	}
	playerInputs.clear();
	InputTracker::UnsubscribeControllerGather();
}

std::list<PlayerInput> ControllerGather::GetControllers()
{
	return playerInputs;
}

void ControllerGather::Update()
{
	bool x = players.size() > 0;
	bool pressedReady = false;
	for (auto player = players.begin(); player != players.end();)
	{
		(*player)->Update(m_allSelected);
		if (!(*player)->IsAlive())
		{
			delete *player;
			player = players.erase(player);
		}
		else {
			x &= (*player)->IsSelected();
			pressedReady |= (*player)->Ready();
			player++;
		}
	}
	m_allSelected = x;
	m_pressedReady = pressedReady;

	if (m_goBack)
	{
		SceneManager::Instance.StartLoadingScene(TitleScene::SCENE);
	}

	if (pressedReady)
	{
		for (auto player : players)
		{
			player->ResetReady();
		}
		IScene::m_menus->push_back(new BattleOptionsMenu(players.size()));
	}
}

void ControllerGather::Draw()
{
	for (auto player : players)
	{
		player->Draw(!m_allSelected);
	}

	if (m_allSelected)
	{
		renderTexture(readyText, Globals::Renderer, 100, Globals::ScreenHeight / 2 - 25);
	}
}

void ControllerGather::RemoveInput(SDL_JoystickID joystickId)
{
	for(auto input = playerInputs.begin(); input != playerInputs.end();)
	{
		if (input->joystickId == joystickId)
		{
			input = playerInputs.erase(input);
		}
		else
			input++;
	}
}

void ControllerGather::SetInput(Uint8 input, SDL_JoystickID joystick)
{
	if (m_pressedReady)
		return;

	for (auto pinput : playerInputs)
	{
		if (pinput.joystickId == joystick)
			return;
	}

	if (playerInputs.size() == 0 && (input == Globals::KeyboardButtons->AltFire || input == SDL_CONTROLLER_BUTTON_X))
	{
		m_goBack = true;
	}

	int pn = 0;
	for (auto input : playerInputs)
	{
		pn += input.playerSpot * input.playerSpot;
	}

	if (pn != 1 && pn != 5 && pn != 10 && pn != 14 && pn != 17 && pn != 21 && pn != 26 && pn != 30)
		pn = 0; //1
	else if (pn != 4 && pn != 5 && pn != 13 && pn != 14 && pn != 20 && pn != 21 && pn != 29 && pn != 30)
		pn = 1; //2
	else if (pn != 9 && pn != 10 && pn != 13 && pn != 14 && pn != 25 && pn != 26 && pn != 29 && pn != 30)
		pn = 2; //3
	else if (pn != 30)
		pn = 3; //4
	else
		return;



	if (joystick >= 0)
		players.push_back(new PlayerSelectEntity(this, joystick, pn));
	else
		players.push_back(new PlayerSelectEntity(this, Globals::KeyboardButtons, pn));

	PlayerInput pinput;
	pinput.joystickId = joystick;
	pinput.playerSpot = pn + 1;
	pinput.taken = true;
	playerInputs.push_back(pinput);
}
