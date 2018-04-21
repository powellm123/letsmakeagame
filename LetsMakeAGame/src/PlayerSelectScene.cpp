
#include "PlayerSelectScene.h"
#include "ControllerGather.h"
#include "Helper_Functions.h"
#include <sstream>

PlayerSelectScene::PlayerSelectScene()
{
}

PlayerSelectScene::~PlayerSelectScene()
{
}

void PlayerSelectScene::Init()
{
	SpriteFactory::AddSpriteSheet("border2.png", "border", 32, 32);
	SpriteFactory::AddSpriteSheet("tanks.png", "tank");
	IScene::m_entities->push_back(new ControllerGather());

	backgroundTexture = GetBackGround();

	SDL_Color color = { 255, 255, 255, 255 };
	std::stringstream ss;

	ss.str("");
	ss << "press 'x' to join";
	helpMessage = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 20, Globals::Renderer);
}

SDL_Texture* PlayerSelectScene::GetBackGround()
{
	SDL_Surface* surface = loadSurface(std::string(Globals::GetResourcePath() + "MainBackGround.png"), Globals::Renderer);
	SDL_Surface* scaledSurface = SDL_CreateRGBSurface(0, Globals::ScreenWidth, Globals::ScreenHeight, 32, 0xFF, 0xFF00, 0xFF0000, 0XFF000000);


	static SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = Globals::ScreenWidth;
	rect.h = Globals::ScreenHeight;
	int error;
	if (error = SDL_BlitScaled(surface, NULL, scaledSurface, &rect))
	{
		std::cout << "Error Happened" << std::endl;
	}

	SDL_Texture* testMap = SDL_CreateTextureFromSurface(Globals::Renderer, scaledSurface);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(scaledSurface);
	return testMap;
}

void PlayerSelectScene::Update()
{
	IScene::Update();
}

void PlayerSelectScene::Draw()
{
	renderTexture(backgroundTexture, Globals::Renderer, 0, 0);

	if (!m_menus->empty())
		m_menus->back()->Draw();

	if (IScene::m_menus->size() == 0)
	{
		for (auto& sprite : *m_spriteobjects)
		{
			sprite->Draw();
		}
		//Draw all entities
		for (auto &it : *m_entities)
		{
			//update all entites in game world at once
			(it)->Draw();
		}
	}

	if (IScene::m_menus->size() == 0) {
		int w, h;
		SDL_QueryTexture(helpMessage, NULL, NULL, &w, &h);
		renderTexture(helpMessage, Globals::Renderer, Globals::ScreenWidth / 2 - w / 2, Globals::ScreenHeight - h);
	}
}
