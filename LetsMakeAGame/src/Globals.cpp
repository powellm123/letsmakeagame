#include "Globals.h"


int Globals::ScreenWidth = 640;
int Globals::ScreenHeight = 352;
int Globals::ScreenScale = 2;

bool Globals::Debugging = true;

SDL_Renderer *Globals::Renderer = nullptr;

std::string Globals::GetResourcePath()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + "\\res\\";
}

std::string Globals::GenerateId()
{
	char id[16];
	for (int i = 0; i < 16; i++)
	{
		int a = (rand() % 36);
		if (a < 10)
			id[i] = char(a + 48);
		else
			id[i] = char(a + 87);
	}
	return std::string(id);
}
