#pragma once

#include "SDL_GraphicsLibrary.h"
#include "Globals.h"
#include "InputTracker.h"
#include "SceneManager.h"
#include "SoundManager.h"

class Game
{
public:
	Game(SDL_GraphicsLibrary *gl);
	~Game();
	void Run();
	void Draw();
	void Update();
	static int Width;
	static int Height;
	static int WidthHalf;
	static int HeightHalf;
private:
	SDL_GraphicsLibrary *m_gl;
};