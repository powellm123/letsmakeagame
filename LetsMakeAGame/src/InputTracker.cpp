
#include "Inputtracker.h"
#include "Menu.h"

std::list<std::pair<SDL_JoystickID, Uint8>*> InputTracker::PressedButtons;
std::list< Uint8> InputTracker::PressedKeyboard;
std::list<std::pair<Player*, SDL_Joystick*>*> InputTracker::links = std::list<std::pair<Player*, SDL_Joystick*>*>();
std::list<Player*> InputTracker::keyboardSubscribers = std::list<Player*>();

void InputTracker::CleanUp()
{
	//// Close if opened
	//if ( SDL_JoystickGetAttached(joystick)) {
	//	SDL_JoystickClose(joystick);
	//}
}

void InputTracker::UpdateKeyboard()
{
	for (auto m_actor : keyboardSubscribers) {
		if (!m_actor->Active)
			continue;
		if(m_actor->GetType() == Menu::type && !((Menu*)m_actor)->GetIsActable())
			continue;
		Buttons m_buttons = *m_actor->GetButtons();
		if (m_buttons.ControllerNumber == -1) {
			const Uint8 *keystates = SDL_GetKeyboardState(nullptr);
			for (auto button : PressedKeyboard) {
				if (button == m_buttons.Fire) {
					((Player*)m_actor)->PerformAction(Player::Action::Fire);
				}
				if (button == m_buttons.AltFire) {
					((Player*)m_actor)->PerformAction(Player::Action::AltFire);
				}
				if (button == m_buttons.Pause) {
					((Player*)m_actor)->PerformAction(Player::Action::Pause);
				}
			}
			//ups
			if (keystates[m_buttons.Up])
			{
				//upright
				if (keystates[m_buttons.Right])
				{
					((Player*)m_actor)->PerformMove(270 + 45, .9);
				}
				else if (keystates[m_buttons.Left])
				{
					((Player*)m_actor)->PerformMove(270 - 45, .9);
				}
				else {
					((Player*)m_actor)->PerformMove(270, .9);
				}
			}
			else if (keystates[m_buttons.Down])
			{
				//downright
				if (keystates[m_buttons.Right])
				{
					((Player*)m_actor)->PerformMove(90 - 45, .9);
				}
				else if (keystates[m_buttons.Left])
				{
					((Player*)m_actor)->PerformMove(90 + 45, .9);
				}
				else {
					((Player*)m_actor)->PerformMove(90, .9);
				}
			}
			else if (keystates[m_buttons.Left])
			{
				((Player*)m_actor)->PerformMove(180, .9);
			}
			else if (keystates[m_buttons.Right])
			{
				((Player*)m_actor)->PerformMove(0, .9);
			}
		}
	}

}

void InputTracker::Update()
{
	RemoveBadActors();

	UpdateKeyboard();

	for (auto pair : links) {
		Buttons m_buttons = *pair->first->GetButtons();
		Player* m_actor = pair->first;
		SDL_Joystick* joystick = pair->second;
		SDL_JoystickID m_joystickId = SDL_JoystickInstanceID(joystick);

		for (auto& pressedButton : PressedButtons)
		{
			if (joystick == nullptr || pressedButton->first != m_joystickId)
				continue;

			auto button = pressedButton->second;
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

		float angle = std::atan2(y, x) * 180 / M_PI;
		float c = x * x + y * y;
		c = std::sqrt(c);
		if (c > deadzone)
			((Player*)m_actor)->PerformMove(angle, c / 1.41421356);

	}
}
void InputTracker::AddButtonPress(SDL_JoystickID joystickId, Uint8 button)
{
	PressedButtons.emplace_back(new std::pair<SDL_JoystickID, Uint8>(joystickId, button));
}

void InputTracker::AddButtonPress(Uint8 button)
{
	PressedKeyboard.emplace_back(button);
}

void InputTracker::CleanButtonPress()
{
	while (!PressedButtons.empty())
		PressedButtons.pop_back();

	while (!PressedKeyboard.empty())
		PressedKeyboard.pop_back();
}

SDL_JoystickID InputTracker::SubscribeToControllerInput(Player * actor, int controllerinput)
{
	if (controllerinput == -1)
	{
		SubscribeToKeyboardInput(actor);
		return NULL;
	}

	auto joystick = SDL_JoystickOpen(controllerinput);
	auto joystickId = SDL_JoystickInstanceID(joystick);

	links.emplace_back(new std::pair<Player*, SDL_Joystick*>(actor, joystick));

	return joystickId;
}

void InputTracker::SubscribeToKeyboardInput(Player * actor)
{
	keyboardSubscribers.emplace_back(actor);
}

void InputTracker::UnsubscribeActor(Player * actor)
{
	for (auto it = links.begin(); it != links.end();)
	{
		if ((*it)->first->GetId() == actor->GetId())
		{
			it = (links).erase((it));
		}
		else {
			it++;
		}
	}


	for (auto it = keyboardSubscribers.begin(); it != keyboardSubscribers.end();)
	{
		if ((*it)->GetId() == actor->GetId())
		{
			it = keyboardSubscribers.erase((it));
		}
		else {
			it++;
		}
	}
}

bool InputTracker::ControllerWork(int controllerinput)
{
	if (controllerinput < 0)
		return false;

	auto joystick = SDL_JoystickOpen(controllerinput);
	return joystick == NULL;
}

void InputTracker::RemoveBadActors()
{
	for (auto it = links.begin(); it != links.end();)
	{
		try {
		if ((*it)->first->GetId() == 0)
		{
			it = (links).erase((it));
		}
		else {
			it++;
		}
		}
		catch (...)
		{
			it = links.erase((it));
		}
	}

	for (auto it = keyboardSubscribers.begin(); it != keyboardSubscribers.end();)
	{
		try {
			if (*it == NULL || *it == nullptr)
				continue;
			if ((*it)->GetId() == 0)
			{
				it = keyboardSubscribers.erase((it));
			}
			else {
				it++;
			}
		}
		catch(...)
		{
			it = keyboardSubscribers.erase((it));
		}
	}
}
