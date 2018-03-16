#pragma once

#include "Entity.h"
#include "Buttons.h"

class Player : public Entity
{
public:
	Player(size_t type, float x, float y, int playernumber, Buttons *buttons, Sprite *sprite);
	Player(size_t type, Buttons* buttons);
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