#pragma once

#include "Entity.h"
#include "Buttons.h"

class Player : public Entity
{
public:
	Player(std::string type, float x, float y, int playernumber, Buttons *buttons, SDL_Sprite *sprite);
	Player(std::string type, Buttons* buttons);
	void Update() override;
	const enum class Action { Up, Down, Left, Right, Fire, AltFire, Pause };

	virtual void PerformAction(Action action) = 0;
	virtual void PerformMove(float angle, float value) = 0;
	Buttons* GetButtons();
	bool IsAlive();
protected:
	bool Alive;
	std::list<Action> m_actions;
	Buttons *m_buttons;
};