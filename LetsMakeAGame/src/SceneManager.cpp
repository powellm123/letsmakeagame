
#include "SceneManager.h"

SceneManager::~SceneManager()
{
}

void SceneManager::LoadScene(std::string name)
{
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
		Entity::RemoveAllFromList(IScene::m_entities, true);
	}

	switch (scenes[UtilMethods::ToLower(name)])
	{
	case 0: //test scene
		currentScene = new TestScene();
		break;

	case 1: //title scene
		currentScene = new TitleScene();
		break;

	default:
		throw "Scene Doesn't exists";
	}

	currentScene->Init();
}

 void SceneManager::Update()
 {
	 currentScene->Update();
 }

 void SceneManager::Draw()
 {
	 currentScene->Draw();
 }

 SceneManager* SceneManager::GetInstance()
{
	static SceneManager* instance = new SceneManager();
	return instance;
}

SceneManager::SceneManager()
{
	scenes["test"] = 0;
	scenes["title"] = 1;

	LoadScene("title");
}