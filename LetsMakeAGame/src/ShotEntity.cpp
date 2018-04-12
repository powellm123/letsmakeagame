
#include "ShotEntity.h"

ShotEntity::ShotEntity(Entity *actor, SDL_Scancode fireButton, int maxShots) : IComponent(actor, "shotentity", type)
{
	fire = fireButton;
	m_maxShots = maxShots;
	shotdist = .3;
	shotcooldownMax = .5;
	shotdistpowerupcount = 0;
	shotcooldownpucount = 0;
	explosionSizeCount = 0;
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
			Movable* moveComponent = (Movable*)this->m_actor->GetComponent(Movable::type);
			auto bullet = new Bullet((int) this->m_actor->X, (int)this->m_actor->Y, moveComponent->GetAngle(), shotdist, explosionSizeCount);
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
			if (m_altfirebullets.size() == 0) {
				SoundManager::Instance.PlayASound(SoundManager::Erk);
			}
			else {
				Entity* bullet = nullptr;
				Movable* moveComponent = (Movable*)this->m_actor->GetComponent(Movable::type);
				switch (m_altfirebullets.front())
				{
				case PowerUp::PowerUpType::CannonBall:
					bullet = new Lob_Bullet(this->m_actor->X, this->m_actor->Y, moveComponent->GetAngle());
					IScene::m_entities->emplace_back(bullet);
					break;
				case PowerUp::PowerUpType::Mine:
					bullet = new Mine(this->m_actor->X, this->m_actor->Y, moveComponent->GetAngle());
					IScene::m_entities->emplace_back(bullet);
					break;
				case PowerUp::PowerUpType::FlameThrower:
					FlameShooter * flameshooterComponent = (FlameShooter*)this->m_actor->GetComponent(FlameShooter::type);
					flameshooterComponent->ShotFire();
					//m_actor.AddComponent( new FlameThrower(this->m_actor->X, this->m_actor->Y, moveComponent->GetAngle()));
					break;
				
				}
				m_altfirebullets.pop_front();
			}
			coolDown = shotcooldownMax;
		}
	}

	if (coolDown > 0)
		coolDown -= TimeController::instance.DeltaTime;


}

void ShotEntity::AddAltShot(PowerUp::PowerUpType powerupType)
{
	m_altfirebullets.push_back(powerupType);
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

void ShotEntity::IncreateExplosionSize()
{
	if (explosionSizeCount < 8)
	{
		explosionSizeCount++;
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

