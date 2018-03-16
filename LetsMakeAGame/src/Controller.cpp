
#include "Controller.h"

Controller::Controller(Player * actor, int controllerNumber) : IComponent(actor, "controller", type)
{
	InputTracker::SubscribeToControllerInput((Player*)actor, controllerNumber);
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


