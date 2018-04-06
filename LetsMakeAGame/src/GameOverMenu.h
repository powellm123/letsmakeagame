#pragma once

#include "IMenu.h"
#include "UtilMethods.h"
#include "SceneManager.h"
#include "Globals.h"
#include "BattleScene.h"

class GameOverMenu : public IMenu
{
	void BackCommand() override
	{
	}
public:
	static constexpr unsigned MenuId = UtilMethods::const_hash("GameOverMenu");
	GameOverMenu() : IMenu(MenuId)
	{
		MenuAction action1;
		action1.name = "PlayAgain";
		action1.action = []() {SceneManager::Instance.StartLoadingScene(BattleScene::SCENE); };
		m_menuActions.push_back(action1);

		MenuAction action2;
		action2.name = "Title Screen";
		action2.action = []() {SceneManager::Instance.StartLoadingScene(TitleScene::SCENE); };
		m_menuActions.push_back(action2);
	}


	void Draw() override
	{
		for (int i = 0; i < m_menuActions.size(); i++)
		{
			SDL_Texture *textTexture;

			//generate score text
			SDL_Color color = { 255, 255, 255, 255 };
			if (i == m_index)
				color = { 35,82,15,255 };
			std::stringstream ss;
			ss << m_menuActions[i].name;

			textTexture = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 25, Globals::Renderer);

			renderTexture(textTexture, Globals::Renderer, Globals::ScreenWidth/2 - 30, Globals::ScreenHeight/2 + 100 + i * 30);
		}
	}
};