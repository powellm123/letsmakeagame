#include "Game.h"

int Game::Width=0;
int Game::Height=0;
int Game::WidthHalf=0;
int Game::HeightHalf=0;

Game::Game(SDL_GraphicsLibrary *gl)
{
	m_gl = gl;
	m_entity = new std::list<Entity*>();
	//m_scene = new TestScene();
	Globals::Quit = false;


	Globals::ControllerButtons->Fire = '\x1';
	Globals::ControllerButtons->AltFire = '\x0';
	Globals::ControllerButtons->Pause = '\t';

	Globals::KeyboardButtons->ControllerNumber = -1;
	Globals::KeyboardButtons->Up = SDL_SCANCODE_UP;
	Globals::KeyboardButtons->Down = SDL_SCANCODE_DOWN;
	Globals::KeyboardButtons->Left = SDL_SCANCODE_LEFT;
	Globals::KeyboardButtons->Right = SDL_SCANCODE_RIGHT;

	Globals::KeyboardButtons->Fire = SDL_SCANCODE_X;
	Globals::KeyboardButtons->AltFire = SDL_SCANCODE_Z;
	Globals::KeyboardButtons->Pause = SDL_SCANCODE_SPACE;
}

Game::~Game()
{
	//delete m_scene;
	Entity::RemoveAllFromList(m_entity, true);
	Entity::RemoveAllFromList(IScene::m_entities, true);
	SceneManager::GetInstance()->~SceneManager();
}

void Game::Run()
{
	SDL_Event e;
	float timer = 1;
	float frameCount = 0;
	Width = Globals::ScreenWidth / 32;
	Height = Globals::ScreenHeight / 32;
	WidthHalf = Globals::ScreenWidth / 2;
	HeightHalf = Globals::ScreenHeight / 2;
	SDL_JoystickEventState(SDL_ENABLE);
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

			case SDL_JOYBUTTONDOWN:
				InputTracker::AddButtonPress(e.jbutton.which, e.jbutton.button);
				break;
			}
		}

		Update();
		Draw();

		InputTracker::CleanButtonPress();

		Entity::RemoveInactiveEntitiesFromList(IScene::m_entities, true);

	}
}

void Game::Update()
{
//	if(m_scene != nullptr)
//		m_scene->Update();
	SceneManager::GetInstance()->Update();

	InputTracker::Update();
}

void Game::Draw()
{
	//clear the screen
	SDL_SetRenderDrawColor(Globals::Renderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Globals::Renderer);

	IScene::m_entities->sort(Entity::EntityCompare);
//	if (m_scene != nullptr)
//		m_scene->Draw();
	SceneManager::GetInstance()->Draw();


	//after finished rendering draw it to the screen
	SDL_RenderPresent(Globals::Renderer);
}