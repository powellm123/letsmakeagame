#pragma once

#include "Entity.h"
#include "Movable.h"
#include "KeyboardInput.h"
#include "Health.h"
#include "ShotEntity.h"
#include "HitBox.h"
#include "PowerUp.h"
#include "Buttons.h"

class Player : public Entity
{
public:
	const enum class Action{Up, Down, Left, Right, Fire, AltFire, Pause};
	const enum PlayerNumber{ Player1 = 1, Player2 = 2, Player3 = 3, Player4 = 4};

	Player(float x, float y, SDL_Sprite *sprite);
	
	void PerformAction(Action action);
	void PerformMove(float angle, float value);
	void Update() override;
	void Draw() override;
	void AddPowerUp(PowerUp *p);
	void DoDamage(int amount);

private:
	std::list<Action> m_actions;
	PlayerNumber m_playernumber;
};