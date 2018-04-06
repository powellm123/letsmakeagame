
#include "OptionsMenu.h"

OptionsMenu::OptionsMenu() : IMenu(MenuId)
{
	MenuAction action1;
	action1.name = "Music";
	action1.action = []() {};
	m_menuActions.push_back(action1);

	MenuAction action2;
	action2.name = "Sound";
	action2.action = []() {};
	m_menuActions.push_back(action2);

	MenuAction action3;
	action3.name = "Controls";
	action3.action = []() {};
	m_menuActions.push_back(action3);

	SDL_Color color = { 255, 255, 255, 255 };
	std::stringstream ss;
	ss << " " << std::string(MusicPlayer::Instance.GetVolumeNumber(), '.');
	musicCount = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);

	ss.str("");
	ss << " " << std::string(SoundManager::Instance.GetVolumeNumber(), '.');
	soundCount = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);
}


void OptionsMenu::Increase()
{
	std::stringstream ss;
	SDL_Color color = { 255, 255, 255, 255 };
	if (m_index == 0)
	{
		MusicPlayer::Instance.IncreaseVolume();
		ss << " " << std::string(MusicPlayer::Instance.GetVolumeNumber(), '.');
		musicCount = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);

	}
	if (m_index == 1)
	{
		SoundManager::Instance.IncreaseVolume();
		ss << " " << std::string(SoundManager::Instance.GetVolumeNumber(), '.');
		soundCount = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);

	}

	m_justSwitched = true;
	m_moveCoolDown = .17;
}

void OptionsMenu::Decrease()
{
	std::stringstream ss;
	SDL_Color color = { 255, 255, 255, 255 };
	if (m_index == 0) {
		MusicPlayer::Instance.DecreaseVolume();
		ss << " " << std::string(MusicPlayer::Instance.GetVolumeNumber(), '.');
		musicCount = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);
	}
	if (m_index == 1) {
		SoundManager::Instance.DecreaseVolume();
		ss << " " << std::string(SoundManager::Instance.GetVolumeNumber(), '.');
		soundCount = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);
	}
	m_justSwitched = true;
	m_moveCoolDown = .17;
}

void OptionsMenu::Update()
{
	if (m_justSwitched)
	{
		if (m_moveCoolDown <= 0)
		{
			m_justSwitched = false;
		}
		else
			m_moveCoolDown -= TimeController::instance.DeltaTime;
		return;
	}

	IMenu::Update();

	for (auto keypress : IMenu::keypresses)
	{
		if (keypress == Globals::KeyboardButtons->Left)
		{
			Decrease();
		}
		if (keypress == Globals::KeyboardButtons->Right)
		{
			Increase();
		}
	}

	for (int i = 0; i < InputTracker::controllerNumberToId.size(); i++)
	{
		static const float deadzone = 0.5;

		float x = SDL_GameControllerGetAxis(SDL_GameControllerFromInstanceID(InputTracker::controllerNumberToId[i]), SDL_CONTROLLER_AXIS_LEFTX) / 32768.0;

		x *= x * x;

		if (x > 0.9)
		{
			Increase();
		}
		if (x < -0.9)
		{
			Decrease();
		}
	}
}

void OptionsMenu::Draw()
{
	IMenu::Draw();
	renderTexture(musicCount, Globals::Renderer, Globals::ScreenWidth / 2 +100, 100 + 0 * 100);
	renderTexture(soundCount, Globals::Renderer, Globals::ScreenWidth / 2+100, 100 + 1 * 100);
}
