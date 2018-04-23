#pragma once

#include "UtilMethods.h"
#include "IMenu.h"
#include "BattleScene.h"
#include "TitleScene.h"
#include "SceneManager.h"

struct ScoreBoard
{
	Sprite *playerSprites[4];
	int points[4];

	int playerCount;
};

class ScoreBoardMenu : public IMenu
{
	SDL_Texture *m_background;
	Sprite *m_tropy0;
	Sprite *m_tropy1;
	Sprite *m_tropy2;
	ScoreBoard m_scoreboard;
	Animation *m_star;
	float waitforAnimation;
	int m_playersPoint;

	void BackCommand() override
	{
	}
public:
	static constexpr unsigned MenuId = UtilMethods::const_hash("ScoreBoardMenu");
	ScoreBoardMenu(ScoreBoard scoreboard, int playersPoint) : IMenu(MenuId)
	{
		m_scoreboard = scoreboard;
		m_playersPoint = playersPoint;
		MenuAction action1;
		action1.name = "Next Match";
		action1.action = []() {SceneManager::Instance.ReinitScene(); };
		m_menuActions.push_back(action1);

		MenuAction action2;
		action2.name = "Quit";
		action2.action = []() {SceneManager::Instance.StartLoadingScene(TitleScene::SCENE); };
		m_menuActions.push_back(action2);

		m_background = IScene::GetTexture("BattleoverBackground.png");
		m_tropy0 = SpriteFactory::GetSprite("trophy", 0);
		m_tropy1 = SpriteFactory::GetSprite("trophy", 1);
		m_tropy2 = SpriteFactory::GetSprite("trophy", 2);
		m_star = SpriteFactory::GetAnimation("trophy", 3, 3);

		waitforAnimation = .5;
	}

	~ScoreBoardMenu()
	{
		delete m_tropy0;
		delete m_tropy1;
		delete m_tropy2;

		cleanup(m_background);
	}

	void Draw() override
	{
		renderTexture(m_background, Globals::Renderer, 0, 0);

		for (int i = 0; i < m_scoreboard.playerCount; i++)
		{
			m_scoreboard.playerSprites[i]->Draw(MathHelper::CreatePoint( 70, (i) * 60 + 100), 1, 1);
			for (int j = 0; j < m_scoreboard.points[i]; j++)
			{
				m_tropy0->Draw(MathHelper::CreatePoint((j + 1) *30+ 75, (i) * 60+100), 1, 1);
			}
		}

		if (waitforAnimation > 0)
			waitforAnimation -= TimeController::instance.DeltaTime;
		else
		{
			m_star->Update();
			m_star->Draw(MathHelper::CreatePoint((m_scoreboard.points[m_playersPoint - 1] + 1) * 30 + 75, (m_playersPoint - 1) * 60 + 100), 1, 1);
		}
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

			renderTexture(textTexture, Globals::Renderer, Globals::ScreenWidth / 2 - 30, Globals::ScreenHeight / 2 + 100 + i * 30);
		}
	}
};