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
	Controller(Player *actor, int controllerNumber);
	~Controller();

	void Update() override;
	void Draw() override;
};