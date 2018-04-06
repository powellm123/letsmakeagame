
#include "Inputtracker.h"
#include "IMenu.h"


std::map<int, SDL_JoystickID> InputTracker::controllerNumberToId;
std::list<std::pair<SDL_JoystickID, Uint8>*> InputTracker::PressedButtons;
std::list< Uint8> InputTracker::PressedKeyboard;
std::list<std::pair<Player*, SDL_GameController*>*> InputTracker::links;
std::list<Player*> InputTracker::keyboardSubscribers;
std::list<IMenu*> InputTracker::menuSubscriber;
ControllerGather* InputTracker::cg_subscriber;
std::list<std::pair<SDL_JoystickID, float>*> InputTracker::cooldown;

void InputTracker::Init()
{
	SDL_JoystickEventState(SDL_ENABLE);
	int haserror = SDL_GameControllerAddMappingsFromFile(std::string(Globals::GetResourcePath() + "gamecontrollerdb.txt").c_str());
	if(haserror == -1)
		std::cout << SDL_GetError();

	int plugedincontrollers = SDL_NumJoysticks();
	for (int i = 0; i < plugedincontrollers; i++)
	{
		auto joystick = SDL_GameControllerOpen(i);

		if (joystick == NULL){
			std::cout << SDL_GetError();
			auto guid = SDL_JoystickGetDeviceGUID(i);
			std::cout << guid.data << std::endl;
		}
		else {
			auto joystickId = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(joystick));

			controllerNumberToId[i] = joystickId;
		}
	}
}

void InputTracker::CleanUp()
{
	// Close if opened
	int plugedincontrollers = SDL_NumJoysticks();
	for (int i = 0; i < plugedincontrollers; i++)
	{
		SDL_GameControllerClose(SDL_GameControllerFromInstanceID(controllerNumberToId[i]));
	}
}

void InputTracker::UpdateKeyboard()
{
	for (auto m_actor : keyboardSubscribers) {
		if (!m_actor->Active)
			continue;
		Buttons m_buttons = *m_actor->GetButtons();
		if (m_buttons.ControllerNumber == -1) {
			const Uint8 *keystates = SDL_GetKeyboardState(nullptr);
			for (auto button : PressedKeyboard) {
				if (button == m_buttons.Fire) {
					((Player*)m_actor)->PerformAction(IPlayer::Action::Fire);
				}
				if (button == m_buttons.AltFire) {
					((Player*)m_actor)->PerformAction(IPlayer::Action::AltFire);
				}
				if (button == m_buttons.Pause) {
					((Player*)m_actor)->PerformAction(IPlayer::Action::Pause);
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
		IPlayer* m_actor = pair->first;
		SDL_GameController* joystick = pair->second;
		SDL_JoystickID m_joystickId = SDL_JoystickInstanceID( SDL_GameControllerGetJoystick(joystick));

		for (auto& pressedButton : PressedButtons)
		{
			if (joystick == nullptr || pressedButton->first != m_joystickId)
				continue;

			auto button = pressedButton->second;
			if (button == SDL_CONTROLLER_BUTTON_A)
				((Player*)m_actor)->PerformAction(IPlayer::Action::Fire);
			if (button == SDL_CONTROLLER_BUTTON_X)
				((Player*)m_actor)->PerformAction(IPlayer::Action::AltFire);
			if (button == SDL_CONTROLLER_BUTTON_START)
				((Player*)m_actor)->PerformAction(IPlayer::Action::Pause);
		}

		static const float deadzone = 0.2;

		float x = SDL_GameControllerGetAxis(joystick, SDL_CONTROLLER_AXIS_LEFTX) / 32768.0;
		float y = SDL_GameControllerGetAxis(joystick, SDL_CONTROLLER_AXIS_LEFTY) / 32768.0;

		float x2 = abs(x) < deadzone ? 0 : x;
		float y2 = abs(y) < deadzone ? 0 : y;

		float angle = std::atan2(y2, x2) * 180 / M_PI;
		angle < 0 ? 360 + angle : angle;
		float c = x2 * x2 + y2 * y2;
		c = std::sqrt(c);
		if (c > deadzone)
			((Player*)m_actor)->PerformMove(angle, c / 1.41421356);

	}

	for(auto it = cooldown.begin(); it != cooldown.end();)
	{
		(*it)->second -= TimeController::instance.DeltaTime;
		if ((*it)->second < 0)
		{
			delete *it;
			it = cooldown.erase(it);
		}
		else
			it++;
	}
}

void InputTracker::AddButtonPress(SDL_JoystickID joystickId, Uint8 button)
{
	for (auto cooldownjoystick : cooldown)
	{
		if (cooldownjoystick->first == joystickId)
			return;
	}
	PressedButtons.emplace_back(new std::pair<SDL_JoystickID, Uint8>(joystickId, button));
	IMenu::AddkeyPress(button);
	if (cg_subscriber != nullptr)
	{
		cg_subscriber->SetInput(button, joystickId);
	}

	cooldown.push_back(new std::pair<SDL_JoystickID, float>(joystickId, .3));
}

void InputTracker::AddButtonPress(Uint8 button)
{
	PressedKeyboard.emplace_back(button);
	IMenu::AddkeyPress(button);
	if (cg_subscriber != nullptr)
	{
		cg_subscriber->SetInput(button, -1);
	}
}

void InputTracker::AddAxisMovement(SDL_JoystickID joystickId, Uint8 axis, int power)
{
}

void InputTracker::CleanButtonPress()
{
	PressedButtons.clear();
	PressedKeyboard.clear();
	IMenu::ClearKeyPress();
}

SDL_JoystickID InputTracker::SubscribeToControllerInput(Player * actor, int controllerinput)
{
	if (controllerinput == -1)
	{
		SubscribeToKeyboardInput(actor);
		return NULL;
	}
	auto joystickId = controllerNumberToId[controllerinput];
	auto joystick = SDL_GameControllerFromInstanceID(joystickId);
	links.emplace_back(new std::pair<Player*, SDL_GameController*>(actor, joystick));

	return joystickId;
}

SDL_JoystickID InputTracker::SubscribeToControllerInput(Player * actor, int controllerinput, SDL_JoystickID joystickId)
{
	auto joystick = SDL_GameControllerFromInstanceID(joystickId);
	links.emplace_back(new std::pair<Player*, SDL_GameController*>(actor, joystick));

	return joystickId;
}

void InputTracker::SubscribeToKeyboardInput(Player * actor)
{
	keyboardSubscribers.emplace_back(actor);
}

void InputTracker::SubscribeControllerGather(ControllerGather * cg)
{
	cg_subscriber = cg;
}

void InputTracker::UnsubscribeControllerGather()
{
	cg_subscriber = nullptr;
}

void InputTracker::UnsubscribeActor(IPlayer * actor)
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
		catch (...)
		{
			it = keyboardSubscribers.erase((it));
		}
	}
}
