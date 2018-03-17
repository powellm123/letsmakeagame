
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


	m_matchend = false;
	testMap = IMG_LoadTexture(Globals::Renderer, std::string(Globals::GetResourcePath() + "map2.png").c_str());

	SpriteFactory::AddSpriteSheet("DessertTileSet.png", "tile");
	SpriteFactory::AddSpriteSheet("poweruptileset.png", "powerup");
	SpriteFactory::AddSpriteSheet("tank.png", "tank");
	SpriteFactory::AddSpriteSheet("bullets.png", "bullet");
	SpriteFactory::AddSpriteSheet("border.png", "border", 32, 32);
	SpriteFactory::AddSpriteSheet("healthbar.png", "healthbar", 32,32);

	Buttons *cb = Globals::ControllerButtons;
	cb->ControllerNumber = 0;
	m_entities->emplace_back(new TankControlledTank(64, 64, 1, Globals::KeyboardButtons));
	m_entities->emplace_back(new CpuTank(Globals::ScreenWidth - 64, Globals::ScreenHeight - 64, 2, cb, map));
	m_entities->emplace_back(new CpuTank( 64, Globals::ScreenHeight - 64, 3, cb, map));
	m_entities->emplace_back(new CpuTank(Globals::ScreenWidth - 64, 64, 4, cb,  map));

	m_entities->emplace_back(new Boarder(0, 0, 32, Globals::ScreenHeight));
	m_entities->emplace_back(new Boarder(Globals::ScreenWidth-32, 16, 32, Globals::ScreenHeight));
	m_entities->emplace_back(new Boarder(0, 0, Globals::ScreenWidth,32));
	m_entities->emplace_back(new Boarder(0, Globals::ScreenHeight-32, Globals::ScreenWidth, 32));

	int countY = Game::Height - 1;
	int countX = Game::Width - 1;
	const int freeroom = 5;
	for (int i = 1; i < countX; i++)
		for (int j = 1; j < countY; j++)
		{
			if (i < freeroom && j < freeroom || i < freeroom && j > countY - freeroom || i > countX - freeroom && j < freeroom || i > countX - freeroom && j > countY - freeroom)
				continue;
			if (i == countX / 2 && j < 3 || i == countX / 2 && j > countY - 3 || i < 3 && j == countY / 2 || i > countX - 3 && j == countY / 2) {
				m_entities->emplace_back(new Wall(i * 32, j * 32)); // SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
				continue;
			}
			if (rand() % 10 < 7) {
				if (rand() % 10 < 1)
					m_entities->emplace_back(new Wall(i * 32 , j * 32 )); //SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
				else
					m_entities->emplace_back(new DirtWall(i * 32 , j * 32 )); //SDL_Sprite::Load(0, 0, 32, 32, "dirtwall.png")));
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