#pragma once

#include "IPlayer.h"
#include "IScene.h"
#include "PlayerSelectEntity.h"

struct PlayerInput
{
	SDL_JoystickID joystickId;
	int playerSpot;
	bool taken;
};

class ControllerGather : public IPlayer
{
private:
	std::list<PlayerSelectEntity*> players;
	std::list<PlayerInput> playerInputs;
	bool m_allSelected = false;
	bool m_pressedReady = false;
	SDL_Texture *readyText;
	bool m_goBack = false;
public:
	static constexpr size_t type = UtilMethods::const_hash("ControllerGather");
	ControllerGather();
	~ControllerGather();
	std::list<PlayerInput> GetControllers();
	void Update() override;
	void Draw() override;
	void RemoveInput(SDL_JoystickID m_joystickId);
	void SetInput(Uint8 input, SDL_JoystickID joystick);
};