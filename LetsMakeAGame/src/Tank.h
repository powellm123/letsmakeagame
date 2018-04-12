#pragma once

#include "Entity.h"
#include "Movable.h"
#include "KeyboardInput.h"
#include "Health.h"
#include "ShotEntity.h"
#include "HitBox.h"
#include "PowerUp.h"
#include "Player.h"
#include "HealthBar.h"

class Tank : public Player
{
public:
	static constexpr size_t type = UtilMethods::const_hash("tank");
	const enum PlayerNumber{ Player1 = 1, Player2 = 2, Player3 = 3, Player4 = 4};

	Tank(float x, float y, int playernumber, int color, Buttons *buttons);
	Tank(float x, float y, int playernumber, int color);
	Tank(float x, float y, int playernumber, int color, SDL_JoystickID joystickId);
	
	void PerformAction(Player::Action action) override;
	void PerformMove(float angle, float value) override;
	void Update() override;
	void Draw() override;
	void AddPowerUp(PowerUp *p);
	void DoDamage(int amount);

private:
	Sprite * m_whiteSprite;
	PlayerNumber m_playernumber;
	HealthBar *m_healthbar;
};