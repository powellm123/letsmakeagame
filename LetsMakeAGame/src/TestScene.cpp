
#include "TestScene.h"
#include "Game.h"
#include "Boarder.h"

TestScene::TestScene() : IScene()
{
	matchendTimer = 5;
	map = new Map(width, height);
}

TestScene::~TestScene()
{
	IScene::~IScene();
	SDL_DestroyTexture(testMap);
	SDL_DestroyTexture(gameOverTexture);
	delete map;
}

void TestScene::Init()
{
	Buttons *b = Globals::KeyboardButtons;
	std::vector<std::string> menu1;
	menu1.push_back("ok");
	m_menu1 = new Menu(menu1, false, false, b, "gameover");
	//m_entities->emplace_back(m_menu1);


	m_matchend = false;
	testMap = IMG_LoadTexture(Globals::Renderer, std::string(Globals::GetResourcePath() + "map2.png").c_str());
	Buttons *cb = Globals::ControllerButtons;
	cb->ControllerNumber = 0;
	m_entities->emplace_back(new TankControlledTank(64, 64, 1, Globals::KeyboardButtons, SDL_Sprite::Load(0, 0, 32, 32, "tank.png")));
	m_entities->emplace_back(new CpuTank(Globals::ScreenWidth - 64, Globals::ScreenHeight - 64, 2, cb, SDL_Sprite::Load(0, 0, 32, 32, "tank.png"), map));
	m_entities->emplace_back(new CpuTank( 64, Globals::ScreenHeight - 64, 3, cb, SDL_Sprite::Load(0, 0, 32, 32, "tank.png"), map));
	m_entities->emplace_back(new CpuTank(Globals::ScreenWidth - 64, 64, 4, cb, SDL_Sprite::Load(0, 0, 32, 32, "tank.png"), map));

	//for (int i = 0; i < Globals::ScreenWidth / 32; i++)
	//{
	//	m_entities->emplace_back(new Wall(i * 32 + 16, 16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
	//	m_entities->emplace_back(new Wall(i * 32 + 16, Globals::ScreenHeight - 16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
	//}
	//for (int i = 1; i < Globals::ScreenHeight / 32 - 1; i++)
	//{
	//	m_entities->emplace_back(new Wall(16, i * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
	//	m_entities->emplace_back(new Wall(Globals::ScreenWidth - 16, i * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
	//}

	m_entities->emplace_back(new Boarder(16, 16, 32, Globals::ScreenHeight));
	m_entities->emplace_back(new Boarder(Globals::ScreenWidth-16,16, 32, Globals::ScreenHeight));
	//m_entities->emplace_back(new Boarder(0, 0, Globals::ScreenWidth-64, 32));
	m_entities->emplace_back(new Boarder(16, Globals::ScreenHeight-16, Globals::ScreenWidth, 32));
	m_entities->emplace_back(new Boarder(16, 16, Globals::ScreenWidth,32));
	//m_entities->emplace_back(new Boarder(Globals::ScreenWidth-64, 0, Globals::ScreenWidth-64, 32));

	int countY = Game::Height - 1;
	int countX = Game::Width - 1;
	const int freeroom = 5;
	for (int i = 1; i < countX; i++)
		for (int j = 1; j < countY; j++)
		{
			if (i < freeroom && j < freeroom || i < freeroom && j > countY - freeroom || i > countX - freeroom && j < freeroom || i > countX - freeroom && j > countY - freeroom)
				continue;
			if (i == countX / 2 && j < 3 || i == countX / 2 && j > countY - 3 || i < 3 && j == countY / 2 || i > countX - 3 && j == countY / 2) {
				m_entities->emplace_back(new Wall(i * 32 + 16, j * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
				continue;
			}
			if (rand() % 10 < 5) {
				//if (rand() % 10 < 3) {
				//	switch (rand() % 3)
				//	{
				//	case 0:
				//		m_entities->emplace_back(new PowerUp(i * 32 + 16, j * 32 + 16, PowerUp::PowerUpType::SpeedUp, SDL_Sprite::Load(0, 0, 32, 32, "powerup.png")));
				//		break;
				//	case 1:
				//		m_entities->emplace_back(new PowerUp(i * 32 + 16, j * 32 + 16, PowerUp::PowerUpType::ShotUp, SDL_Sprite::Load(0, 0, 32, 32, "shotup.png")));
				//		break;
				//	case 2:
				//		m_entities->emplace_back(new PowerUp(i * 32 + 16, j * 32 + 16, PowerUp::PowerUpType::ShotCountUp, SDL_Sprite::Load(0, 0, 32, 32, "shotcountup.png")));
				//		break;

				//	}
				//	m_entities->emplace_back(new DirtWall(i * 32 + 16, j * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "dirtwall.png")));
				//}
				if (rand() % 10 < 1)
					m_entities->emplace_back(new Wall(i * 32 + 16, j * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
				else
					m_entities->emplace_back(new DirtWall(i * 32 + 16, j * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "dirtwall.png")));
			}
		}

	//generate score text
	SDL_Color color = { 255, 255, 255, 255 };
	std::stringstream ss;
	ss << "Game Over";

	gameOverTexture = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);


	std::string message = "Press X To Start!";
	text = renderText(message, std::string(Globals::GetResourcePath() + "Lato-Black.ttf"), color, 25, Globals::Renderer);
}


void TestScene::Update()
{
	map->PopulateMap();
	//map->Print();
	if (!m_matchend && GetAliveCount() <= 1)
	{
		m_matchend = true;
	}


	if (!m_matchend) {
		IScene::Update();
	}
	else
	{
		if (matchendTimer > 0) {
			matchendTimer -= TimeController::instance.DeltaTime;
		}
		else {
			Menu::ChangeActiveMenu(m_menu1);
		}
		if ((m_menu1)->GetIsActionSelected())
		{
			std::string action = (m_menu1)->GetSelectedAction();

			if (action == "ok")
			{
				SceneManager::GetInstance()->LoadScene("test");
			}

		}
	}
}

void TestScene::Draw()
{

	//Draw the Background
	renderTexture(testMap, Globals::Renderer, 0, 0);

	//update all entities
	for (auto &it : *m_entities)
	{
		//update all entites in game world at once
		(it)->Draw();
	}
	
	IScene::Draw();

	if (m_matchend) {
		int w, h;
		SDL_QueryTexture(gameOverTexture, NULL, NULL, &w, &h);
		renderTexture(gameOverTexture, Globals::Renderer, Game::WidthHalf - w / 2, Game::HeightHalf - h / 2);

		if (matchendTimer <= 0) {
			int tw, th;
			SDL_QueryTexture(text, NULL, NULL, &tw, &th);

			renderTexture(text, Globals::Renderer, Game::WidthHalf + (tw/2), Game::HeightHalf + h / 2 + th);
		}
	}

}