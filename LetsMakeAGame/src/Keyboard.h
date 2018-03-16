#pragma once
#include "Player.h"
#include "IComponent.h"
#include "Inputtracker.h"

class Keyboard : public IComponent
{
public:
	static constexpr size_t type = UtilMethods::const_hash("keyboard");
	Keyboard(Player* entity) : IComponent(entity, "keyboard") 
	{
		InputTracker::SubscribeToKeyboardInput(entity);
	}
	virtual ~Keyboard()
	{
		InputTracker::UnsubscribeActor((Player*)m_actor);
	}

	void Update() override{}
	void Draw() override {}
};