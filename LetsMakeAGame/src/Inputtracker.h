#pragma once

#include <list>
#include "SDL.h"
#include "Player.h" 

class InputTracker
{
public:
	static void CleanUp();
	static void Update();
	static void UpdateKeyboard();
	static void AddButtonPress(SDL_JoystickID joystickId, Uint8 button);
	static void AddButtonPress(Uint8 button);
	static void CleanButtonPress();
	static SDL_JoystickID SubscribeToControllerInput(Player* actor, int controllerinput);
	static void SubscribeToKeyboardInput(Player* actor);
	static void UnsubscribeActor(Player* actor);
	static bool ControllerWork(int controllerinput);
	static void	RemoveBadActors();
private:
	static std::list<std::pair<SDL_JoystickID, Uint8>*> PressedButtons;
	static std::list< Uint8> PressedKeyboard;
	static std::list<std::pair<Player*, SDL_Joystick*>*> links;
	static std::list<Player*> keyboardSubscribers;
};