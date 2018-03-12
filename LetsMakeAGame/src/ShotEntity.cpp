
#include "ShotEntity.h"

ShotEntity::ShotEntity(Entity *actor, SDL_Scancode fireButton, int maxShots) : IComponent(actor, "shotentity")
{
	fire = fireButton;
	m_maxShots = maxShots;
	shotdist = .3;
	shotcooldownMax = .5;
	shotdistpowerupcount = 0;
	shotcooldownpucount = 0;
}

void ShotEntity::Update()
{
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	if (m_performFireAction)
	{
		m_performFireAction = false;
		m_performAltAction = false;
		if (coolDown <= 0)
		{
			Movable* moveComponent = (Movable*)this->m_actor->GetComponent("movable");
			auto bullet = new Bullet( this->m_actor->X, this->m_actor->Y, moveComponent->GetAngle(), shotdist);
			IScene::m_entities->emplace_back(bullet);
			coolDown = shotcooldownMax;
		}

	}
	else if (m_performAltAction)
	{
		m_performFireAction = false;
		m_performAltAction = false;
		if (coolDown <= 0)
		{
			Movable* moveComponent = (Movable*)this->m_actor->GetComponent("movable");
			auto bullet = new Lob_Bullet(this->m_actor->X, this->m_actor->Y, moveComponent->GetAngle());
			IScene::m_entities->emplace_back(bullet);
			coolDown = shotcooldownMax;
		}
	}

	if (coolDown > 0)
		coolDown -= TimeController::instance.DeltaTime;


}

void ShotEntity::IncreaseMaxShot()
{
	if (shotdistpowerupcount < 8)
	{
		shotdist += .05;
		shotdistpowerupcount++;
	}
}

void ShotEntity::IncreaseMaxShotCount()
{
	if (shotcooldownpucount < 8)
	{
		shotcooldownMax -= .05;
		shotcooldownpucount++;
	}

}

void ShotEntity::ShouldPerformFireAction()
{
	m_performFireAction = true;
}

void ShotEntity::ShouldPerformAltFireAction()
{
	m_performAltAction = true;
}

void ShotEntity::Draw()
{
}

