
#include "Controller.h"


std::list<std::pair<SDL_JoystickID, Uint8>> Controller::PressedButtons;

Controller::Controller(Entity * actor,  Buttons *buttons) : IComponent(actor, "controller"), m_buttons(*buttons)
{
	static int joystickNumber = 0;
	joystick = SDL_JoystickOpen(joystickNumber++);

	m_joystickId = SDL_JoystickInstanceID(joystick);
	
}

Controller::~Controller()
{
	// Close if opened
	if (SDL_JoystickGetAttached(joystick)) {
		SDL_JoystickClose(joystick);
	}
}

void Controller::Update()
{
	for (auto& pressedButton : PressedButtons)
	{
		if (pressedButton.first != m_joystickId)
			continue;

		auto button = pressedButton.second;
		if (button == m_buttons.Fire)
			((Player*)m_actor)->PerformAction(Player::Action::Fire);
		if (button == m_buttons.AltFire)
			((Player*)m_actor)->PerformAction(Player::Action::AltFire);

		if (button == m_buttons.Pause)
			((Player*)m_actor)->PerformAction(Player::Action::Pause);

	}
	static const float deadzone = 0.5;

	float x = SDL_JoystickGetAxis(joystick, 0) / 32768.0;
	float y = SDL_JoystickGetAxis(joystick, 1) / 32768.0;

	x = abs(x) < deadzone ? 0 : x;
	y = abs(y) < deadzone ? 0 : y;

	float angle = std::atan2(y, x) * 180/M_PI;
	float c = x * x + y * y;
	c = std::sqrt(c);
	if(c > deadzone)
		((Player*)m_actor)->PerformMove(angle, c/1.41421356);
}

void Controller::Draw()
{
}

void Controller::AddButtonPress(SDL_JoystickID joystickId, Uint8 button)
{
	PressedButtons.emplace_back(std::pair<SDL_JoystickID, Uint8>(joystickId, button));
}

void Controller::CleanButtonPress()
{
	while (!PressedButtons.empty())
		PressedButtons.pop_back();
}
