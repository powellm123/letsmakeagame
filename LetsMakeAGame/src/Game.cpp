#include "Game.h"

int Game::Width=0;
int Game::Height=0;
int Game::WidthHalf=0;
int Game::HeightHalf=0;

Game::Game(SDL_GraphicsLibrary *gl)
{
	m_gl = gl;
	Globals::Quit = false;
	Globals::InitKeyboardKeys();

	SoundManager::Instance.Init();
	InputTracker::Init();

	Width = Globals::ScreenWidth / 32;
	Height = Globals::ScreenHeight / 32;
	WidthHalf = Globals::ScreenWidth / 2;
	HeightHalf = Globals::ScreenHeight / 2;

	SceneManager::Instance.Init();
}

Game::~Game()
{
	//delete m_scene;
	Entity::RemoveAllFromList(IScene::m_entities, true);
	SceneManager::Instance.~SceneManager();
}

void Game::Run()
{
	SDL_Event e;
	float timer = 1;
	float frameCount = 0;
	while (!Globals::Quit)
	{
		TimeController::instance.UpdateTime();
		//if (Globals::Debugging) {
			timer -= TimeController::instance.DeltaTime;
			if (timer <= 0)
			{
				std::cout << frameCount;
				timer = 1;
				frameCount = 0;
			}
			frameCount++;
		//}

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				Globals::Quit = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					Globals::Quit = true;
					break;
				default:
					InputTracker::AddButtonPress(e.key.keysym.scancode);
					break;
				}
				break;

			case SDL_CONTROLLERBUTTONDOWN:
				InputTracker::AddButtonPress(e.cbutton.which, e.cbutton.button);
				break;
			case SDL_CONTROLLERAXISMOTION:
				InputTracker::AddAxisMovement(e.caxis.which, e.caxis.axis, e.caxis.value);
				break;
			}
		}

		Update();
		Draw();

		InputTracker::CleanButtonPress();

		Entity::RemoveInactiveEntitiesFromList(IScene::m_entities, true);
		IScene::RemoveInactiveSpriteObjects();
	}
}

void Game::Update()
{
	SceneManager::Instance.Update();

	InputTracker::Update();
}

void Game::Draw()
{
	//clear the screen
	SDL_SetRenderDrawColor(Globals::Renderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Globals::Renderer);

	SceneManager::Instance.Draw();

	//after finished rendering draw it to the screen
	SDL_RenderPresent(Globals::Renderer);
}