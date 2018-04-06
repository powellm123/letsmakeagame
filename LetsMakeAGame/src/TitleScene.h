#pragma once

#include "IScene.h"

class TitleScene : public IScene
{
public:
	static constexpr size_t SCENE = UtilMethods::const_hash("titlescene");
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
	void Init() override;
private:
	SDL_Texture * GetTitle();
	static bool m_showTitle;
	bool m_showtext;
	float m_toggleText;
	SDL_Texture * testMap;
	SDL_Texture * text;
	int textTextureWidth;
	int textTextureHeight;
};