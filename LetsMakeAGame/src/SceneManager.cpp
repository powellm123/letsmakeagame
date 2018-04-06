
#include "SceneManager.h"
#include "PlayerSelectScene.h"
#include "BattleScene.h"

SceneManager SceneManager::Instance;

SceneManager::SceneManager()
{
}

void SceneManager::Init()
{
	LoadScene(TitleScene::SCENE);
}

SceneManager::~SceneManager()
{
	Entity::RemoveAllFromList(IScene::m_entities, true);
	delete currentScene;
	currentScene = nullptr;
}

void SceneManager::StartLoadingScene(size_t scene)
{
	prepScene = scene;
}

void SceneManager::LoadScene(size_t scene)
{
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
		Entity::RemoveAllFromList(IScene::m_entities, true);
	}

	switch (scene)
	{
	case TestScene::SCENE:
		currentScene = new TestScene();
		break;

	case TitleScene::SCENE:
		currentScene = new TitleScene();
		break;

	case PlayerSelectScene::SCENE:
		currentScene = new PlayerSelectScene();
		break;

	case BattleScene::SCENE:
		currentScene = new BattleScene();
		break;
	default:
		throw "Scene Doesn't exists";
	}

	currentScene->Init();
}

 void SceneManager::Update()
 {
	 if (prepScene != 0)
	 {
		 LoadScene(prepScene);
		 prepScene = 0;
	 }
	 currentScene->Update();
 }

 void SceneManager::Draw()
 {
	 IScene::m_entities->sort(Entity::EntityCompare);
	 currentScene->Draw();
 }

