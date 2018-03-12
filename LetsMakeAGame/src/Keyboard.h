#pragma once
#include "Player.h"
#include "IComponent.h"
#include "Inputtracker.h"

class Keyboard : public IComponent
{
public:
	Keyboard(Player* entity) : IComponent(entity, "keyboard") 
	{
		InputTracker::SubscribeToKeyboardInput(entity);
	}
	~Keyboard()
	{
		InputTracker::UnsubscribeActor((Player*)m_actor);
	}

	void Update() override{}
	void Draw() override {}
};