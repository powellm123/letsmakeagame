
#include "IMenu.h"
#include <sstream>
#include "Globals.h"
#include "Helper_Functions.h"
#include "InputTracker.h"
#include "IScene.h"


std::list<Uint8> IMenu::keypresses;

void IMenu::BackCommand()
{
	IScene::m_menus->pop_back();
}

IMenu::IMenu(unsigned menuId) : m_menuId(menuId)
{
}

unsigned IMenu::GetMenuId()
{
	return m_menuId;
}

void IMenu::Update()
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

	for (auto keypress : IMenu::keypresses)
	{
		if (keypress == SDL_CONTROLLER_BUTTON_A || keypress == Globals::KeyboardButtons->Fire  || keypress == SDL_CONTROLLER_BUTTON_START || keypress == Globals::KeyboardButtons->Pause)
		{
			m_menuActions[m_index].action();
		}
		if (keypress == SDL_CONTROLLER_BUTTON_X || keypress == Globals::KeyboardButtons->AltFire)
		{
			BackCommand();
		}
		if (keypress == Globals::KeyboardButtons->Up)
		{
			m_index = max(0, m_index - 1);
		}
		//if (keypress == Globals::KeyboardButtons->Left)
		//{
		//}
		if (keypress == Globals::KeyboardButtons->Down)
		{
			m_index = min(m_menuActions.size()-1, m_index + 1);
		}
		//if (keypress == Globals::KeyboardButtons->Right)
		//{
		//}
	}

	for (int i = 0; i < InputTracker::controllerNumberToId.size(); i++)
	{
		static const float deadzone = 0.5;

		float y = SDL_GameControllerGetAxis(SDL_GameControllerFromInstanceID( InputTracker::controllerNumberToId[i]), SDL_CONTROLLER_AXIS_LEFTY) / 32768.0;

		y *= y * y;

		if (y > 0.9)
		{
			m_justSwitched = true;
			m_index = min(m_menuActions.size() - 1, m_index + 1);
			m_moveCoolDown = .17;
		}
		if (y < -0.9)
		{
			m_justSwitched = true;
			m_index = max(0, m_index - 1);
			m_moveCoolDown = .17;
		}
	}
	if (m_moveCoolDown > 0)
		m_moveCoolDown -= TimeController::instance.DeltaTime;
}

void IMenu::Draw()
{
	for (int i = 0; i < m_menuActions.size(); i++)
	{
		SDL_Texture *scoreTexture;

		//generate score text
		SDL_Color color = { 255, 255, 255, 255 };
		if (i == m_index)
			color = { 35,82,15,255 };
		std::stringstream ss;
		ss << m_menuActions[i].name;

		scoreTexture = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 60, Globals::Renderer);

		renderTexture(scoreTexture, Globals::Renderer, 20, 100 + i * 100);
	}
}

void IMenu::ClearKeyPress()
{
	keypresses.clear();
}

void IMenu::AddkeyPress(Uint8 key)
{
	keypresses.push_back(key);
}
