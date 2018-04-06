#pragma once

#include "IScene.h"

class PlayerSelectScene : public IScene
{
	SDL_Texture* backgroundTexture;
	SDL_Texture* helpMessage;
public:
	static constexpr size_t SCENE = UtilMethods::const_hash("playerselectscene");
	PlayerSelectScene();
	~PlayerSelectScene();
	void Init() override;
	void Update() override;
	void Draw() override;
	SDL_Texture* GetBackGround();
};