#pragma once

#include "IComponent.h"
#include "Player.h"
#include "SDL.h"
#include <list>
#include "Buttons.h"
#include "Inputtracker.h"

class Controller : public IComponent
{
public:
	static constexpr size_t type = UtilMethods::const_hash("controller");
	Controller(Player *actor, int controllerNumber);
	Controller(Player *actor, int controllerNumber, SDL_JoystickID joystickId);
	virtual ~Controller();

	void Update() override;
	void Draw() override;
};