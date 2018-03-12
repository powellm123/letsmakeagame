#pragma once

#include <map>
#include <memory>
#include "IScene.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "UtilMethods.h"

class SceneManager
{
public:
	~SceneManager();
	void LoadScene(std::string name);

	void Update();
	void Draw();
	
	static SceneManager* GetInstance();


private:
	SceneManager();
	std::map<std::string, int> scenes;
	IScene *currentScene;
};

