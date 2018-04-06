#pragma once

#include <list>
#include "SDL.h"
#include "Player.h" 
#include "IMenu.h"
#include "ControllerGather.h"

class InputTracker
{
public:
	static void Init();
	static void CleanUp();
	static void Update();
	static void UpdateKeyboard();
	static void AddButtonPress(SDL_JoystickID joystickId, Uint8 button);
	static void AddButtonPress(Uint8 button);
	static void AddAxisMovement(SDL_JoystickID joystickId, Uint8 axis, int power);
	static void CleanButtonPress();
	static SDL_JoystickID SubscribeToControllerInput(Player* actor, int controllerinput);
	static SDL_JoystickID SubscribeToControllerInput(Player* actor, int controllerinput, SDL_JoystickID joystickId);
	static void SubscribeToKeyboardInput(Player* actor);
	static void SubscribeControllerGather(ControllerGather* cg);
	static void UnsubscribeControllerGather();
	static void UnsubscribeActor(IPlayer* actor);
	static bool ControllerWork(int controllerinput);
	static void	RemoveBadActors();
	static std::map<int, SDL_JoystickID> controllerNumberToId;
private:
	static std::list<std::pair<SDL_JoystickID, Uint8>*> PressedButtons;
	static std::list<Uint8> PressedKeyboard;
	static std::list<std::pair<Player*, SDL_GameController*>*> links;
	static std::list<Player*> keyboardSubscribers;
	static std::list<IMenu*> menuSubscriber;
	static ControllerGather* cg_subscriber;
	static std::list<std::pair<SDL_JoystickID, float>*> cooldown;
};