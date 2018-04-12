#pragma once

#include "Player.h"
#include "SDL.h"
#include "SpriteFactory.h"
#include "PlayerSelectBoarder.h"

class ControllerGather;

class PlayerSelectEntity : public Player
{
private:
	int m_currentSprite = 0;
	float m_justChanged = 0;
	bool m_selected = false;
	PlayerSelectBoarder* boarder;
	ControllerGather* m_cg;
	SDL_JoystickID m_joystickId = -1;
	SDL_Texture *readyText;
	bool m_isReady = false;
	bool m_ready = false;
public:
	static constexpr size_t type = UtilMethods::const_hash("PlayerSelectEntity");
	PlayerSelectEntity(ControllerGather* cg, Buttons *buttons, int playerNumber);
	PlayerSelectEntity(ControllerGather* cg, SDL_JoystickID joystickId, int playerNumber);
	~PlayerSelectEntity();
	bool IsSelected();
	void ResetReady();
	bool Ready();
	int GetCurrentSpirte();
	void PerformAction(Player::Action action) override;
	void PerformMove(float angle, float value) override;
	void Update(bool isReady);
	void Draw(bool drawReady);
};