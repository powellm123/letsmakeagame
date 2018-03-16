#include "Menu.h"
#include "Controller.h"
#include "IScene.h"
#include "Helper_Functions.h"

Menu::Menu(std::vector<std::string> menuActions, bool isActable, bool shouldDrawText, Buttons* buttons, std::string menuName) : Player(type, buttons), m_menuActions(menuActions), 
		m_index(0), m_isActionSelected(false), m_selectedAction(""), m_menuName(menuName), m_isActable(isActable)
{
	m_shouldDrawText = shouldDrawText;
}

void Menu::PerformAction(Player::Action action)
{
	switch (action)
	{
	case Player::Action::Fire:
		FireAction();
		break;
	case Player::Action::AltFire:
		AltFireAction();
		break;
	case Player::Action::Pause:
		PauseAction();
		break;
	}
}

void Menu::PerformMove(float angle, float value)
{
	MoveAction(angle);
}

void Menu::Update()
{
	while (!m_actions.empty())
		m_actions.pop_back();

	if (!m_isActable)
		return;

	if( m_justSwitched) {
		if (m_moveCoolDown <= 0)
		{
			m_justSwitched = false;
		}
		else
			m_moveCoolDown -= TimeController::instance.DeltaTime;
		return;
	}

	for (auto& component : *m_components)
	{
		component->Update();
	}

	if (m_moveCoolDown > 0)
		m_moveCoolDown -= TimeController::instance.DeltaTime;
}

void Menu::Draw()
{
	if (m_isActable && m_shouldDrawText)
	{
		for(int i = 0; i < m_menuActions.size(); i++)
		{
			SDL_Texture *scoreTexture;

			//generate score text
			SDL_Color color = { 255, 255, 255, 255 };
			if (i == m_index)
				color = { 35,82,15,255 };
			std::stringstream ss;
			ss << m_menuActions[i];

			scoreTexture = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 60, Globals::Renderer);

			renderTexture(scoreTexture, Globals::Renderer, 20, 100 + i * 100);
		}
	}

}


bool Menu::GetIsActable()
{
	return m_isActable;
}

void Menu::SetIsActable(bool isActable)
{
	m_isActable = isActable;
}

std::string Menu::GetMenuName()
{
	return m_menuName;
}


bool Menu::GetIsActionSelected()
{
	return m_isActionSelected;
}

std::string Menu::GetSelectedAction()
{
	return m_selectedAction;
}

void Menu::FireAction()
{
	m_isActionSelected = true;
	m_selectedAction = m_menuActions[m_index];
}

void Menu::AltFireAction()
{
	m_isActionSelected = true;
	m_selectedAction = "cancel";
}

void Menu::MoveAction(float angle)
{
	if (m_moveCoolDown > 0) {
		m_moveCoolDown = .05;
		return;
	}
	if (angle > 45 && angle < 225)
		m_index = m_index < m_menuActions.size()-1 ? m_index +1 : m_index;
	if (angle < 45 || angle > 225)
			m_index = m_index > 0 ? m_index - 1 : m_index;

	m_moveCoolDown = .05;
}

void Menu::PauseAction()
{
	FireAction();
}

Menu *Menu::GetActiveMenu()
{
	for (auto entity : *IScene::m_entities)
	{
		if (entity->GetType() == Menu::type && ((Menu*)entity)->GetIsActable())
		{
			return (Menu*)entity;
		}
	}

	return nullptr;
}


void Menu::ChangeActiveMenu(Menu *menu)
{
	Menu* oldActiveMenu = GetActiveMenu();
	if(oldActiveMenu != nullptr)
		oldActiveMenu->SetIsActable(false);
	menu->SetIsActable(true);
	menu->m_justSwitched = true;
	menu->m_moveCoolDown = 10;
}

Menu* Menu::FindMenu(std::string menuName)
{
	for (auto entity : *IScene::m_entities)
	{
		if (entity->GetType() == Menu::type && ((Menu*)entity)->m_menuName == menuName)
		{
			return ((Menu*)entity);
		}
	}

	return nullptr;
}

std::list<Menu*>* Menu::GetAllMenus()
{
	std::list<Menu*>* menus = new std::list<Menu*>();
	for (auto entity : *IScene::m_entities)
	{
		if (entity->GetType() == Menu::type)
		{
			menus->push_back((Menu*)entity);
		}
	}
	return menus;
}
