
#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene() : m_showTitle(true)
{
	m_toggleText = 1;
	m_showtext = true;
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

	Menu *activeMenu = Menu::GetActiveMenu();

	if (activeMenu != nullptr && activeMenu->GetIsActionSelected())
	{
		std::string action = (activeMenu)->GetSelectedAction();

		if (action == "ok")
		{
			Menu* menu2 = Menu::FindMenu("main");
			Menu::ChangeActiveMenu(menu2);
			m_showTitle = false;
		}
		/*if (action == "cancel")
		{
			(*m_activeMenu)->SetIsVisable(false);
			m_activeMenu = &m_menu1;
			(*m_activeMenu)->SetIsVisable(true);
		}*/
		if (action == "playgame")
		{
			SceneManager::GetInstance()->LoadScene("test");
		}
		if (action == "quit")
		{
			Globals::Quit = true;
		}
	}

	else if ( activeMenu != nullptr && activeMenu->GetMenuName() == "title")
	{
		if (m_toggleText <= 0)
		{
			m_showtext = !m_showtext;
			m_toggleText = .61 + .4 * m_showtext;
		}
		m_toggleText -= TimeController::instance.DeltaTime;
		
	}
}

void TitleScene::Draw()
{
	IScene::Draw();
	Menu *activeMenu = Menu::GetActiveMenu();
	if (activeMenu != nullptr && activeMenu->GetMenuName() == "title") //  m_menu1->GetIsVisable())
	{
		//Draw the Background.
		renderTexture(testMap, Globals::Renderer, 0, 0);

		if (m_showtext)
		{
			renderTexture(text, Globals::Renderer, Globals::ScreenWidth / 2 - textTextureWidth / 2, Globals::ScreenHeight - textTextureHeight - 32);
		}
	}

	//sort all entites based on y(depth)
	//m_entities.sort(Entity::EntityCompare);

	//update all entities
	for (auto &it : *m_entities)
	{
		//update all entites in game world at once
		(it)->Draw();
	}
}

void TitleScene::Init()
{
	Buttons *b = Globals::KeyboardButtons;

	testMap = GetTitle();
	std::vector<std::string> menu1;
	menu1.push_back("ok");
	std::vector<std::string> menu2;
	menu2.push_back("playgame");
	menu2.push_back("options");
	menu2.push_back("quit");

	m_entities->emplace_back(new Menu(menu1, true, false, b, "title"));
	m_entities->emplace_back(new Menu(menu2, false, true, b, "main"));

	std::string message = "Press X To Start!";
	SDL_Color color = { 255,255,255,255 };
	text = renderText(message, std::string( Globals::GetResourcePath() + "Lato-Black.ttf"), color, 25, Globals::Renderer);
	SDL_QueryTexture(text, NULL, NULL, &textTextureWidth, &textTextureHeight);

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