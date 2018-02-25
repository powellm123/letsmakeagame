#pragma once

#include "IComponent.h"
#include "IScene.h"
#include <list>
#include <SDL.h>
#include "Bullet.h"
#include "Movable.h"

class ShotEntity : public IComponent
{
public:
	ShotEntity(Entity *actor, SDL_Scancode fireButton, int maxShots) : IComponent(actor, "shotentity") 
	{
		fire = fireButton;
		m_maxShots = maxShots;
	}
	void Update() override
	{
		const Uint8* keys = SDL_GetKeyboardState(nullptr);
		if (m_performFireAction)
		{
			m_performFireAction = false;
			if (coolDown <= 0)
			{
				Movable* moveComponent = (Movable*)this->m_actor->GetComponent("movable");
				auto bullet = new Bullet(SDL_Sprite::Load(0, 0, 8, 15, "bullet.png"), this->m_actor->X, this->m_actor->Y, moveComponent->GetAngle());
				IScene::m_entities->emplace_back(bullet);
				coolDown = .5;
			}

		}

		if(coolDown > 0)
			coolDown -= TimeController::instance.DeltaTime;


	}

	void ShouldPerformFireAction()
	{
		m_performFireAction = true;
	}

	void Draw() override
	{
	}

protected:
	bool m_performFireAction;
	float coolDown;
	SDL_Scancode fire;
	int m_maxShots;
};