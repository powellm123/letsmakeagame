#include "BattleScene.h"
#include <sstream>
#include "Helper_Functions.h"
#include "SpriteFactory.h"
#include "CpuTank.h"
#include "TankControlledTank.h"
#include "Game.h"
#include "Boarder.h"
#include "GameOverMenu.h"

BattleScene::BattleScene()
{
	startlocations[0] = std::pair<int, int>(64, 64);
	startlocations[1] = std::pair<int, int>(Globals::ScreenWidth - 64, 64);
	startlocations[2] = std::pair<int, int>(64, Globals::ScreenHeight - 64);
	startlocations[3] = std::pair<int, int>(Globals::ScreenWidth - 64, Globals::ScreenHeight - 64);
	
	m_timebeforestart = 8;
	m_level = LevelCreator::Instance.BuildLevel();

	matchendTimer = 1;
	map = new Map(width, height);
}

BattleScene::~BattleScene()
{
	SDL_DestroyTexture(testMap);
	SDL_DestroyTexture(gameOverTexture);
	delete map;
}

void BattleScene::Init()
{
	std::vector<std::string> menu1;
	menu1.push_back("ok");

	loading = GetTexture("loading.png");  //IMG_LoadTexture(Globals::Renderer, std::string(Globals::GetResourcePath() + "/loading.png").c_str());
	m_matchend = false;
	testMap = GetTexture(m_level.mapname); // IMG_LoadTexture(Globals::Renderer, std::string(Globals::GetResourcePath() + m_level.mapname).c_str());

	SpriteFactory::AddSpriteSheet("DessertTileSet.png", "tile");
	SpriteFactory::AddSpriteSheet("poweruptileset.png", "powerup");
	SpriteFactory::AddSpriteSheet("tank.png", "tank");
	SpriteFactory::AddSpriteSheet("bullets.png", "bullet");
	SpriteFactory::AddSpriteSheet("border.png", "border", 32, 32);
	SpriteFactory::AddSpriteSheet("healthbar.png", "healthbar", 32, 32);

	for (int i = 0; i < m_level.humanPlayers; i++)
	{
		std::pair<int, int> loc = startlocations[i];
		if(m_level.joysticks[i] >= 0)
			m_entities->emplace_back(new Tank(loc.first, loc.second, i + 1, m_level.joysticks[i]));
		else
			m_entities->emplace_back(new TankControlledTank(loc.first, loc.second, i + 1, Globals::KeyboardButtons)); // m_level.joysticks[i]));
	}

	for (int i = 0; i < m_level.cpuPlayers; i++)
	{
		std::pair<int, int> loc = startlocations[i + m_level.humanPlayers];
		m_entities->emplace_back(new CpuTank(loc.first, loc.second, i + m_level.humanPlayers+1, map));
	}

	m_entities->emplace_back(new Boarder(0, 0, 32, Globals::ScreenHeight));
	m_entities->emplace_back(new Boarder(Globals::ScreenWidth - 32, 16, 32, Globals::ScreenHeight));
	m_entities->emplace_back(new Boarder(0, 0, Globals::ScreenWidth, 32));
	m_entities->emplace_back(new Boarder(0, Globals::ScreenHeight - 32, Globals::ScreenWidth, 32));

	int countY = Game::Height - 1;
	int countX = Game::Width - 1;
	const int freeroom = 5;
	for (int i = 1; i < countX; i++)
		for (int j = 1; j < countY; j++)
		{
			if (i < freeroom && j < freeroom || i < freeroom && j > countY - freeroom || i > countX - freeroom && j < freeroom || i > countX - freeroom && j > countY - freeroom)
				continue;
			if (i == countX / 2 && j < 3 || i == countX / 2 && j > countY - 3 || i < 3 && j == countY / 2 || i > countX - 3 && j == countY / 2) {
				m_entities->emplace_back(new Wall(i * 32, j * 32));
				continue;
			}
			if (rand() % 10 < 7) {
				if (rand() % 10 < 1)
					m_entities->emplace_back(new Wall(i * 32, j * 32));
				else
					m_entities->emplace_back(new DirtWall(i * 32, j * 32));
			}
		}

	//generate score text
	SDL_Color color = { 255, 255, 255, 255 };
	std::stringstream ss;
	ss << "Game Over";

	gameOverTexture = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 80, Globals::Renderer);


	std::string message = "Get Ready!";
	getReady = renderText(message, std::string(Globals::GetResourcePath() + "Bombardment.ttf"), color, 100, Globals::Renderer);

	 message = "Start!";
	start = renderText(message, std::string(Globals::GetResourcePath() + "Bombardment.ttf"), color, 100, Globals::Renderer);

	auto id = MusicPlayer::Instance.LoadSong("GrungeStreet.mp3");
	MusicPlayer::Instance.PlaySong(id);
}

void BattleScene::Update()
{
	if (m_timebeforestart > 0)
	{
		m_timebeforestart -= TimeController::instance.DeltaTime;
		return;
	}

	static bool pushedOnce = false;
	map->PopulateMap();
	//map->Print();
	if (!m_matchend && GetAliveCount() <= 1)
	{
		m_matchend = true;
	}

	IScene::Update();

	if (m_matchend) {
		if (matchendTimer > 0) {
			matchendTimer -= TimeController::instance.DeltaTime;
			pushedOnce = false;
		}
		else {
			if (!pushedOnce) {
				m_menus->push_back(new GameOverMenu());
				pushedOnce = true;
			}
		}
	}
}

void BattleScene::Draw()
{
	if (m_timebeforestart > 3) {
		renderTexture(loading, Globals::Renderer, 0,0);
		return;
	}

	int w, h;
	IScene::Draw();

	//Draw the Background
	renderTexture(testMap, Globals::Renderer, 0, 0);

	//update all entities
	for (auto &it : *m_entities)
	{
		//update all entites in game world at once
		(it)->Draw();
	}

	IScene::Draw();


	if (m_timebeforestart > 1)
	{
		SDL_QueryTexture(getReady, NULL, NULL, &w, &h);
		renderTexture(getReady, Globals::Renderer, Game::WidthHalf - w / 2, Game::HeightHalf - h / 2);
	}

	if (m_timebeforestart > 0 && m_timebeforestart < 1)
	{
		SDL_QueryTexture(start, NULL, NULL, &w, &h);
		renderTexture(start, Globals::Renderer, Game::WidthHalf - w / 2, Game::HeightHalf - h / 2);
	}

	if (m_matchend) {
		SDL_QueryTexture(gameOverTexture, NULL, NULL, &w, &h);
		renderTexture(gameOverTexture, Globals::Renderer, Game::WidthHalf - w / 2, Game::HeightHalf - h / 2);
	}
}
