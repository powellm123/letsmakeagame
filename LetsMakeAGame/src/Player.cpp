
#include "Player.h"
#include "Controller.h"


Player::Player(float x, float y, SDL_Sprite *sprite) : Entity("tank", x, y, sprite)
{
	static int playernumber = 1;
	m_playernumber = (PlayerNumber)playernumber++;
	//if (playernumber == PlayerNumber::Player1)
	//	m_components->push_back(new KeyboardInput(this));
	Buttons *b = new Buttons();
	b->Fire = '\x1';
	b->AltFire = '\x0';
	b->Pause = '\t';
	m_components->push_back(new Movable(this, 10));
	m_components->push_back(new HealthComponent(this, 3));
	m_components->push_back(new ShotEntity(this, SDL_SCANCODE_X, 5));
	m_components->push_back(new HitBox(this, 32, 32, -16));

	m_components->push_back(new Controller(this, b));
}

void Player::PerformAction(Action action)
{
	m_actions.emplace_back(action);
}

void Player::PerformMove(float angle, float power)
{
	Movable* comp = (Movable*)GetComponent("movable");
	float modpower = power > 1 ? 1 : power;
	modpower = power < -1 ? -1 : modpower;
	comp->Move(angle, modpower * comp->GetUseMoveSpeed());
}

void Player::Update()
{
	for (auto& action : m_actions)
	{
		switch (action)
		{
		case Action::Fire:
			ShotEntity * comp = (ShotEntity*)GetComponent("shotentity");
			comp->ShouldPerformFireAction();
		}
	}

	while (!m_actions.empty())
		m_actions.pop_back();

	Entity::Update();
}

void Player::Draw()
{
	Movable *movableComponent = (Movable*) GetComponent("movable");
	m_sprite->Draw(Globals::Renderer, X, Y, movableComponent->GetAngle()+90);
	for (auto& component : *m_components)
	{
		component->Draw();
	}
}

void Player::AddPowerUp(PowerUp *p)
{
	switch (p->GetPowerUpType())
	{
	case PowerUp::PowerUpType::SpeedUp:
		((Movable*)GetComponent("movable"))->IncreaseMaxSpeed();
		break;
	}
}

void Player::DoDamage(int amount)
{
	HealthComponent *health = (HealthComponent*)GetComponent("Health");
	health->Damage(amount);
}
