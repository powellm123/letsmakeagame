#include "LevelSelectMenu.h"
#include "Inputtracker.h"

LevelSelectMenu::LevelSelectMenu() : IMenu(MenuId)
{
	MenuAction action1;
	action1.name = " ";
	action1.action = []() {};
	m_menuActions.push_back(action1);

	levels[0] = std::pair<std::string, std::string>("dirt", "dirtmap3.png");
	levels[1] = std::pair<std::string, std::string>("ice", "icemap2.png");


	m_levelMap = LoadImage(m_levelIndex);

	SDL_Color color = { 255, 255, 255, 255 };
	std::stringstream ss;
	ss << levels[m_levelIndex].first;

	m_levelName = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 60, Globals::Renderer);


	ss.str("");
	ss << "press 'space' to continue";
	helpMessage = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 20, Globals::Renderer);
}

SDL_Texture* LevelSelectMenu::LoadImage(int index)
{
	index = min(max(index, 0), levels.size());
	SDL_Surface* surface = loadSurface(std::string(Globals::GetResourcePath() + levels[index].second), Globals::Renderer);
	SDL_Surface* scaledSurface = SDL_CreateRGBSurface(0, Globals::ScreenWidth, Globals::ScreenHeight, 32, 0xFF, 0xFF00, 0xFF0000, 0XFF000000);


	static SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = Globals::ScreenWidth - 150;
	rect.h = Globals::ScreenHeight - 150;
	int error;
	if (error = SDL_BlitScaled(surface, NULL, scaledSurface, &rect))
	{
		std::cout << "Error Happened" << std::endl;
	}

	auto texture = SDL_CreateTextureFromSurface(Globals::Renderer, scaledSurface);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(scaledSurface);

	return texture;
}

void LevelSelectMenu::Increase()
{
	m_levelIndex = min(levels.size() - 1, m_levelIndex + 1);
	cleanup(m_levelMap);
	m_levelMap = LoadImage(m_levelIndex);


	SDL_Color color = { 255, 255, 255, 255 };
	std::stringstream ss;
	ss << levels[m_levelIndex].first;

	m_levelName = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 60, Globals::Renderer);

	m_justSwitched = true;
	m_moveCoolDown = .17;
}

void LevelSelectMenu::Decrease()
{
	m_levelIndex = max(0, m_levelIndex - 1);
	cleanup(m_levelMap);
	m_levelMap = LoadImage(m_levelIndex);

	SDL_Color color = { 255, 255, 255, 255 };
	std::stringstream ss;
	ss << levels[m_levelIndex].first;

	m_levelName = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 60, Globals::Renderer);

	m_justSwitched = true;
	m_moveCoolDown = .17;
}

void LevelSelectMenu::Update()
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
		if (keypress == SDL_CONTROLLER_BUTTON_START || keypress == Globals::KeyboardButtons->Pause)
		{
			LevelCreator::Instance.SetLevelSkin(levels[m_levelIndex].second);
			SceneManager::Instance.StartLoadingScene(BattleScene::SCENE);
		}

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

void LevelSelectMenu::Draw()
{
	renderTexture(m_levelMap, Globals::Renderer, 75, 100);
	int w, h;
	SDL_QueryTexture(m_levelName, NULL, NULL, &w, &h);
	renderTexture(m_levelName, Globals::Renderer, Globals::ScreenWidth / 2 - w / 2, 50);


	SDL_QueryTexture(helpMessage, NULL, NULL, &w, &h);
	renderTexture(helpMessage, Globals::Renderer, Globals::ScreenWidth / 2 - w / 2, Globals::ScreenHeight - h);
}