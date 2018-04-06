#pragma once

#include "IPlayer.h"
#include "Buttons.h"

class Player : public IPlayer
{
public:
	Player(size_t type, float x, float y, Buttons *buttons, Sprite *sprite);
	Player(size_t type, float x, float y, SDL_JoystickID joystickId, Sprite *sprite);
	Player(size_t type, float x, float y, Sprite *sprite);
	Player(size_t type, Buttons* buttons);
	Player(size_t type, SDL_JoystickID joystickId);
	Buttons* GetButtons();
	void Update() override;
	bool IsAlive();

	virtual void PerformAction(Action action) = 0;
	virtual void PerformMove(float angle, float value) = 0;
protected:
	bool Alive;
	Buttons m_buttons;
};