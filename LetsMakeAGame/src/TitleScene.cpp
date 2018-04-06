
#include "TitleScene.h"
#include "SceneManager.h"
#include "OptionsMenu.h"
#include "AwaitKeyPressMenu.h"

bool TitleScene::m_showTitle = true;

TitleScene::TitleScene()
{
	m_toggleText = 1;
	m_showtext = true;
	m_menus->push_back(new AwaitKeyPressMenu([]()
	{
		IScene::m_menus->push_back(new MainMenu());
		TitleScene::m_showTitle = false;
	}));
}


TitleScene::~TitleScene()
{
	IScene::~IScene();
	SDL_DestroyTexture(testMap);
	SDL_DestroyTexture(text);
}

void TitleScene::Update()
{
	IScene::Update();

	if (m_toggleText <= 0)
	{
		m_showtext = !m_showtext;
		m_toggleText = .61 + .4* m_showtext;
	}
	m_toggleText -= TimeController::instance.DeltaTime;
}

void TitleScene::Draw()
{
	IScene::Draw();

	//Draw the Background.
	if (m_menus->back()->GetMenuId() == AwaitKeyPressMenu::MenuId)
	{
		renderTexture(testMap, Globals::Renderer, 0, 0);

		if (m_showtext)
		{
			renderTexture(text, Globals::Renderer, Globals::ScreenWidth / 2 - textTextureWidth / 2, Globals::ScreenHeight - textTextureHeight - 32);
		}
	}
	else
	{
		std::cout << "";
	}

	//update all entities
	for (auto &it : *m_entities)
	{
		//update all entites in game world at once
		(it)->Draw();
	}
}

void TitleScene::Init()
{
	testMap = GetTitle();

	std::string message = "Press X To Start!";
	SDL_Color color = { 255,255,255,255 };
	text = renderText(message, std::string(Globals::GetResourcePath() + "Lato-Black.ttf"), color, 25, Globals::Renderer);
	SDL_QueryTexture(text, NULL, NULL, &textTextureWidth, &textTextureHeight);

	auto id = MusicPlayer::Instance.LoadSong("Steamtech-Mayhem.mp3");
	MusicPlayer::Instance.PlaySong(id);
}

SDL_Texture* TitleScene::GetTitle()
{
	SDL_Surface* surface = loadSurface(std::string(Globals::GetResourcePath() + "title2.png"), Globals::Renderer);
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