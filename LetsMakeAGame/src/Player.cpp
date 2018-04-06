#include "Player.h"
#include "Controller.h"

Player::Player(size_t type, float x, float y, Buttons *b, Sprite * sprite) : IPlayer(type, x, y, sprite), Alive(true)
{
	m_buttons = *b;
	m_components->push_back(new Controller(this, b->ControllerNumber));
	m_setActiveToFalse = false;
}

Player::Player(size_t type, float x, float y, SDL_JoystickID joystickId, Sprite * sprite) : IPlayer(type, x, y, sprite), Alive(true)
{
	m_components->push_back(new Controller(this, 0, joystickId));
	m_setActiveToFalse = false;
}

Player::Player(size_t type, float x, float y, Sprite * sprite) : IPlayer(type, x, y, sprite), Alive(true)
{
	m_setActiveToFalse = false;
}

Player::Player(size_t type, Buttons *buttons) : IPlayer(type, 0, 0), Alive(true)
{
	m_buttons = *buttons;
	m_components->push_back(new Controller(this, buttons->ControllerNumber));
	m_setActiveToFalse = false;
}

Player::Player(size_t type, SDL_JoystickID joystickId) : IPlayer(type, 0, 0), Alive(true)
{
	m_components->push_back(new Controller(this, 0, joystickId));
	m_setActiveToFalse = false;
}

void Player::Update()
{
	while (!m_actions.empty())
		m_actions.pop_back();
	if (Alive)
	{
		Entity::Update();
	}
	if (GetIsDying())
		Alive = false;
}

Buttons* Player::GetButtons()
{
	return &m_buttons;
}

bool Player::IsAlive()
{
	return Alive;
}
