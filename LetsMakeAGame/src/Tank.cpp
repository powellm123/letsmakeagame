
#include "Tank.h"
#include "Controller.h"

Tank::Tank(float x, float y, int playernumber, Buttons *buttons, Sprite *sprite) : Player(type, x, y, playernumber, buttons, sprite)
{
	//static int playernumber = 1;
	m_playernumber = (PlayerNumber)playernumber;
	
	m_components->push_back(new Movable(this, 12));
	m_components->push_back(new HealthComponent(this, 3));
	m_components->push_back(new ShotEntity(this, SDL_SCANCODE_X, 5));
	m_components->push_back(new HitBox(this, 32, 32, -16));

	IScene::m_spriteobjects->push_back(new HealthBar(this, 10 + playernumber * 125, 20));

}

void Tank::PerformAction(Action action)
{
	m_actions.emplace_back(action);
}

void Tank::PerformMove(float angle, float power)
{
	if (!Alive)
		return;
	Movable* comp = (Movable*)GetComponent(Movable::type);
	float modpower = power > 1 ? 1 : power;
	modpower = power < -1 ? -1 : modpower;
	comp->Move(angle, modpower * comp->GetUseMoveSpeed());
}

void Tank::Update()
{
	if (Alive) {
		for (auto& action : m_actions)
		{
			ShotEntity * comp = (ShotEntity*)GetComponent(ShotEntity::type);
			switch (action)
			{
			case Action::Fire:
				comp->ShouldPerformFireAction();
				break;
			case Action::AltFire:
				comp->ShouldPerformAltFireAction();
				break;
			}
		}
	}


	Player::Update();
}

void Tank::Draw()
{
	if (!Alive)
		return;
	Movable *movableComponent = (Movable*) GetComponent(Movable::type);
	m_sprite->Draw(MathHelper::CreatePoint( X, Y), movableComponent->GetAngle()+90, MathHelper::CreatePoint(1, 1));
	for (auto& component : *m_components)
	{
		component->Draw();
	}

}

void Tank::AddPowerUp(PowerUp *p)
{
	switch (p->GetPowerUpType())
	{
	case PowerUp::PowerUpType::SpeedUp:
		((Movable*)GetComponent(Movable::type))->IncreaseMaxSpeed();
		break;
	case PowerUp::PowerUpType::ShotUp:
		((ShotEntity*)GetComponent(ShotEntity::type))->IncreaseMaxShot();
		break;
	case PowerUp::PowerUpType::ShotCountUp:
		((ShotEntity*)GetComponent(ShotEntity::type))->IncreaseMaxShotCount();
		break;
	case PowerUp::PowerUpType::ExplosionUp:
		((ShotEntity*)GetComponent(ShotEntity::type))->IncreateExplosionSize();
		break;
	}
}

void Tank::DoDamage(int amount)
{
	HealthComponent *health = (HealthComponent*)GetComponent(HealthComponent::type);
	health->Damage(amount);
}
