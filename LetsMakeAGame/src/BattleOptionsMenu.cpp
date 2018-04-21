
#include "BattleOptionsMenu.h"
#include "Inputtracker.h"

BattleOptionsMenu::BattleOptionsMenu(int playerCount) : IMenu(MenuId), m_playerCount(playerCount)
{
	MenuAction action1;
	action1.name = "Cpus";
	action1.action = []() {};
	m_menuActions.push_back(action1);

	m_cpus = max(m_playerCount == 1 ? 1 : 0, m_cpus - 1);

	SDL_Color color = { 255, 255, 255, 255 };
	std::stringstream ss;
	ss << m_cpus;

	cpuCountTexture = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);

	MenuAction action2;
	action2.name = "Hits";
	action2.action = []() {};
	m_menuActions.push_back(action2);

	ss.str("");
	ss << m_hits;
	hitCountTexture = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);

	ss.str("");
	ss << "press 'space' to continue";
	helpMessage = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 20, Globals::Renderer);
}

void BattleOptionsMenu::Increase()
{
	std::stringstream ss;
	SDL_Color color = { 255, 255, 255, 255 };
	if (m_index == 0)
	{
		m_cpus = min(4 - m_playerCount, m_cpus + 1);
		cleanup(cpuCountTexture);

		ss << m_cpus;

		cpuCountTexture = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);

	}
	if (m_index == 1)
	{
		m_hits = min(5, m_hits + 1);
		cleanup(hitCountTexture);

		ss << m_hits;

		hitCountTexture = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);

	}
	m_justSwitched = true;
	m_moveCoolDown = .17;

}

void BattleOptionsMenu::Decrease()
{
	std::stringstream ss;
	SDL_Color color = { 255, 255, 255, 255 };
	if (m_index == 0) {
		m_cpus = max(m_playerCount == 1 ? 1 : 0, m_cpus - 1);
		cleanup(cpuCountTexture);

		ss << m_cpus;

		cpuCountTexture = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);
	}
	if (m_index == 1) {
		m_hits = max(1, m_hits - 1);
		cleanup(hitCountTexture);

		ss << m_hits;

		hitCountTexture = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);
	}

	m_justSwitched = true;
	m_moveCoolDown = .17;
}

void BattleOptionsMenu::Update()
{
	IMenu::Update();

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

	for (auto keypress : IMenu::keypresses)
	{
		if (keypress == SDL_CONTROLLER_BUTTON_START || keypress == Globals::KeyboardButtons->Pause)
		{
			auto gc = IScene::GetEntiries(ControllerGather::type);
			LevelCreator::Instance.AddHumanPlayer(m_playerCount)->
				AddCpuPlayer(m_cpus)->
				AddControllers(((ControllerGather*)gc.front())->GetControllers())->
				AddTankChoose(((ControllerGather*)gc.front())->GetTankChoose());
			IScene::m_menus->push_back(new LevelSelectMenu());
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
void BattleOptionsMenu::Draw()
{
	IMenu::Draw();
	renderTexture(cpuCountTexture, Globals::Renderer, Globals::ScreenWidth / 2, 100 + 0 * 100);
	renderTexture(hitCountTexture, Globals::Renderer, Globals::ScreenWidth / 2, 100 + 1 * 100);
	int w, h;
	SDL_QueryTexture(helpMessage, NULL, NULL, &w, &h);
	renderTexture(helpMessage, Globals::Renderer, Globals::ScreenWidth / 2 - w/2, Globals::ScreenHeight - h);
}