
#include "Controller.h"

Controller::Controller(Player * actor, int controllerNumber) : IComponent(actor, "controller", type)
{
	InputTracker::SubscribeToControllerInput((Player*)actor, controllerNumber);
}

Controller::Controller(Player * actor, int controllerNumber, SDL_JoystickID joystickId) : IComponent(actor, "controller", type)
{
	InputTracker::SubscribeToControllerInput((Player*)actor, controllerNumber, joystickId);
}

Controller::~Controller()
{
	InputTracker::UnsubscribeActor((Player*)m_actor);
}

void Controller::Update()
{
}

void Controller::Draw()
{
}


