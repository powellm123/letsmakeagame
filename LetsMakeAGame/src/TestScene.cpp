
#include "TestScene.h"

TestScene::TestScene() : IScene()
{
	testMap = IMG_LoadTexture(Globals::Renderer, std::string(Globals::GetResourcePath() + "map.png").c_str());
	
	m_entities->emplace_back(new Player(64,64, SDL_Sprite::Load(0, 0, 32, 32, "tank.png")));
	m_entities->emplace_back(new Player(Globals::ScreenWidth - 64, Globals::ScreenHeight - 64, SDL_Sprite::Load(0, 0, 32, 32, "tank.png")));
	//m_entities->emplace_back(new PowerUp(Globals::ScreenWidth/2,Globals::ScreenHeight/2, PowerUp::PowerUpType::SpeedUp,  SDL_Sprite::Load(0,0,32, 32, "powerup.png")));

	for (int i = 0; i < Globals::ScreenWidth / 32; i++)
	{
		m_entities->emplace_back(new Wall(i * 32+16, 16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
		m_entities->emplace_back(new Wall(i * 32+16, Globals::ScreenHeight-16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
	}
	for (int i = 1; i < Globals::ScreenHeight / 32 - 1; i++)
	{
		m_entities->emplace_back(new Wall(16, i * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
		m_entities->emplace_back(new Wall( Globals::ScreenWidth- 16, i * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
	}
	
	int countY = Globals::ScreenHeight / 32 - 1;
	int countX = Globals::ScreenWidth / 32 - 1;

	for (int i = 1; i < countX; i++)
		for (int j = 1; j < countY; j++)
		{
			if (i < 4 && j < 4 || i < 4 && j > countY - 4 || i > countX - 4 && j < 4 || i > countX - 4 && j > countY -4)
				continue;
			if (i == countX / 2 && j < 3 || i == countX/2 && j > countY -3 || i < 3 && j == countY/2 || i > countX - 3 && j == countY / 2) {
				m_entities->emplace_back(new Wall(i * 32 + 16, j * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
				continue;
			}
			if (rand() % 10 < 8) {
				if (rand() % 10 < 3) {
					m_entities->emplace_back(new PowerUp(i * 32 + 16, j * 32 + 16, PowerUp::PowerUpType::SpeedUp, SDL_Sprite::Load(0, 0, 32, 32, "powerup.png")));
					m_entities->emplace_back(new DirtWall(i * 32 + 16, j * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "dirtwall.png")));
				}
				else if(rand() % 10 < 1)
					m_entities->emplace_back(new Wall(i * 32 + 16, j * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "wall.png")));
				else
					m_entities->emplace_back(new DirtWall(i * 32 + 16, j * 32 + 16, SDL_Sprite::Load(0, 0, 32, 32, "dirtwall.png")));
			}
		}
}

TestScene::~TestScene()
{
	SDL_DestroyTexture(testMap);

}

void TestScene::Update()
{
	IScene::Update();
}

void TestScene::Draw()
{
	IScene::Draw();

	//Draw the Background
	renderTexture(testMap, Globals::Renderer, 0, 0);


	//sort all entites based on y(depth)
	//m_entities.sort(Entity::EntityCompare);

	//update all entities
	for (auto &it : *m_entities )
	{
		//update all entites in game world at once
		(it)->Draw();
	}

}