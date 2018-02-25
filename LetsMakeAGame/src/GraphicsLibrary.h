#pragma once

#include <string>
#include <stdint.h>

class IGraphicsLibrary
{
public:
	virtual bool Init() = 0;
	virtual bool InitWindow(std::string& title, int screenWidth, int screenHeight, int screenScale, uint32_t windowFlags) = 0;
	virtual bool CreateRender() = 0;
	virtual void Quit() = 0;

	virtual void CleanUp() = 0;

	virtual bool InitTextToFontLibrary() = 0;
	virtual bool InitAudioLibrary() = 0;
	virtual bool InitImageGraphics() = 0;

	virtual void Draw() = 0;
	virtual void ClearScreen() = 0;
};

class ITextToFontLibrary
{
public:
	virtual bool Init() = 0;
};

class IAudioLibrary
{
public:
	virtual bool Init() = 0;
};

template <class Renderer, class Texture>
class IImageGraphics
{
public:
	virtual bool Init() = 0;
	virtual Texture* Load(const std::string &file, Renderer *ren) = 0;
};