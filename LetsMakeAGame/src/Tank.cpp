
#include "Tank.h"
#include "Controller.h"


Tank::Tank(float x, float y, int playernumber, Buttons *buttons, SDL_Sprite *sprite) : Player("tank", x, y, playernumber, buttons, sprite)
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
	Movable* comp = (Movable*)GetComponent("movable");
	float modpower = power > 1 ? 1 : power;
	modpower = power < -1 ? -1 : modpower;
	comp->Move(angle, modpower * comp->GetUseMoveSpeed());
}

void Tank::Update()
{
	if (Alive) {
		for (auto& action : m_actions)
		{
			ShotEntity * comp = (ShotEntity*)GetComponent("shotentity");
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
	Movable *movableComponent = (Movable*) GetComponent("movable");
	m_sprite->Draw(Globals::Renderer, X, Y, movableComponent->GetAngle()+90);
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
		((Movable*)GetComponent("movable"))->IncreaseMaxSpeed();
		break;
	case PowerUp::PowerUpType::ShotUp:
		((ShotEntity*)GetComponent("shotentity"))->IncreaseMaxShot();
		break;
	case PowerUp::PowerUpType::ShotCountUp:
		((ShotEntity*)GetComponent("shotentity"))->IncreaseMaxShotCount();
		break;
	}
}

void Tank::DoDamage(int amount)
{
	HealthComponent *health = (HealthComponent*)GetComponent("Health");
	health->Damage(amount);
}
