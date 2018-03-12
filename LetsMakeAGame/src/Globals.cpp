#include "Globals.h"

#include "DateTime.h"

Buttons *Globals::ControllerButtons = new Buttons();
Buttons *Globals::KeyboardButtons = new Buttons();

bool Globals::Quit = false;
int Globals::ScreenWidth;
int Globals::ScreenHeight;
int Globals::ScreenScale;

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
	static const int IdLength = 32;
	char id[IdLength];
	DateTime dt = DateTime::Now();
	id[0] = IntToChar(dt.year);
	id[1] = IntToChar(dt.month);
	id[2] = IntToChar(dt.day);
	id[3] = IntToChar(dt.hour);
	
	for (int i = 4; i < IdLength-1; i++)
	{
		int a = (rand() % 36);
		id[i] = IntToChar(a);
	}
	id[IdLength - 1] = '\0';
	return std::string(id);
}

char Globals::IntToChar(int number)
{
	if (number > 36)
		number %= 36;
	if (number < 10)
		return char(number + 48);
	else
		return char(number + 87);
}