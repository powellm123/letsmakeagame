#include "Game.h"

Game::Game(SDL_GraphicsLibrary *gl)
{
	m_gl = gl;
	m_entity = new std::list<Entity*>();
	m_scene = new TestScene();
}

Game::~Game()
{
	delete m_scene;
	Entity::RemoveAllFromList(m_entity, true);
	Entity::RemoveAllFromList(IScene::m_entities, true);
}

void Game::Run()
{
	bool quit = false;
	SDL_Event e;

	SDL_JoystickEventState(SDL_ENABLE);
	while (!quit)
	{
		TimeController::instance.UpdateTime();

		Entity::RemoveInactiveEntitiesFromList(IScene::m_entities, true);

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
				break;

			case SDL_JOYBUTTONDOWN:
				Controller::AddButtonPress(e.jbutton.which, e.jbutton.button);
				break;
			}
		}

		Update();
		Draw();

		Controller::CleanButtonPress();
	}
}

void Game::Update()
{
	if(m_scene != nullptr)
		m_scene->Update();
}

void Game::Draw()
{
	//clear the screen
	SDL_SetRenderDrawColor(Globals::Renderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Globals::Renderer);

	if (m_scene != nullptr)
		m_scene->Draw();


	//after finished rendering draw it to the screen
	SDL_RenderPresent(Globals::Renderer);
}