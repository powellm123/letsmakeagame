#pragma once

#include <map>
#include <memory>
#include "IScene.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "UtilMethods.h"

class SceneManager
{
	SceneManager();
	void LoadScene(size_t scene);
public:
	~SceneManager();
	void StartLoadingScene(size_t scene);
	void Init();
	void Update();
	void Draw();
	
	static SceneManager Instance;
private:
	size_t prepScene = 0;
	IScene *currentScene;
};

