#pragma once

#include "IScene.h"
#include "Menu.h"

class TitleScene : public IScene
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
	void Init() override;
private:
	//Menu * m_menu1;
	//Menu * m_menu2;
	//Menu ** m_activeMenu;
	SDL_Texture * GetTitle();
	bool m_showTitle;
	bool m_showtext;
	float m_toggleText;
	SDL_Texture * testMap;
	SDL_Texture * text;
	int textTextureWidth;
	int textTextureHeight;
};