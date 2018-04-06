#pragma once

#include "IMenu.h"
#include "UtilMethods.h"
#include "Globals.h"
#include "Inputtracker.h"
#include "SoundManager.h"
#include "MusicPlayer.h"
#include <sstream>
#include "Helper_Functions.h"

class OptionsMenu : public IMenu
{
	SDL_Texture* soundCount;
	SDL_Texture* musicCount;
public:
	static constexpr unsigned MenuId = UtilMethods::const_hash("OptionsMenu");
	OptionsMenu();
	void Update() override;
	void Draw() override;

	void Increase();
	void Decrease();
};