#pragma once

#include "IMenu.h"
#include "PlayerSelectScene.h"
#include "SceneManager.h"

class MainMenu : public IMenu
{
public:
	static constexpr unsigned MenuId = UtilMethods::const_hash("MainMenu");
	MainMenu() : IMenu(MenuId)
	{
		MenuAction action1;
		action1.name = "Play Game";
		action1.action = []() { SceneManager::Instance.StartLoadingScene(PlayerSelectScene::SCENE); };
		m_menuActions.push_back(action1);

		MenuAction action2;
		action2.name = "Options";
		action2.action = []() {IScene::m_menus->push_back(new OptionsMenu()); };
		m_menuActions.push_back(action2);

		MenuAction action3;
		action3.name = "Quit";
		action3.action = [] { Globals::Quit = true; };
		m_menuActions.push_back(action3);
	}
};