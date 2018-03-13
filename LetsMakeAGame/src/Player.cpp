#include "Player.h"
#include "Controller.h"

Player::Player(std::string type, float x, float y, int playernumber, Buttons *b, SDL_Sprite * sprite) : Entity(type, x, y, sprite), Alive(true)
{
	m_buttons = b;
	m_components->push_back(new Controller(this, b->ControllerNumber));
	m_setActiveToFalse = false;
}

Player::Player(std::string type, Buttons *buttons) : Entity(type, 0, 0), Alive(true)
{
	m_buttons = buttons;
	m_components->push_back(new Controller(this, buttons->ControllerNumber));
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
	return m_buttons;
}

bool Player::IsAlive()
{
	return Alive;
}
