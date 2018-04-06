
#include "FlameShooter.h"

FlameShooter::FlameShooter(Entity* actor) : IComponent(actor, "FlameShooter", type)
{
	m_maxshottimes = .3;
}

void FlameShooter::ShotFire()
{
	m_shottime = 1.5;
}

void FlameShooter::Update()
{
	if (m_shottime > 0)
	{
		m_shottime -= TimeController::instance.DeltaTime;
		if (m_nextshot <= 0) {

			Movable* moveComponent = (Movable*)this->m_actor->GetComponent(Movable::type);
			auto bullet = new FlameThrower(this->m_actor->X, this->m_actor->Y, moveComponent->GetAngle());
			IScene::m_entities->push_back(bullet);
			m_nextshot = m_maxshottimes;
		}
		else {
			m_nextshot -= TimeController::instance.DeltaTime;
		}
	}
}

void FlameShooter::Draw()
{
}

