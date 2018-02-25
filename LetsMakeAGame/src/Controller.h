#pragma once

#include "IComponent.h"
#include "Player.h"
#include "SDL.h"
#include <list>
#include "Buttons.h"

class Controller : public IComponent
{
public:
	Controller(Entity *actor, Buttons *buttons);
	~Controller();
	void Update() override;
	void Draw() override;

	static void AddButtonPress(SDL_JoystickID joystickId, Uint8 button);
	static void CleanButtonPress();
	

private:
	SDL_JoystickID m_joystickId;
	Buttons m_buttons;
	SDL_Joystick *joystick;
	static std::list<std::pair<SDL_JoystickID, Uint8>> PressedButtons;
};