#include "Bullet.h"
#include "Movable.h"
#include "HitBox.h"
#include "Explosion.h"


Bullet::Bullet(SDL_Sprite *sprite, float x, float y, float angle, float lifespan) : Entity("bullet", 0, 0, sprite)
{
	this->X = x + cos(angle*M_PI /180)*30;
	this->Y = y + sin(angle*M_PI /180)*30;
	this->Angle = angle;
	this->Active = true;

	LifeSpan = lifespan;

	m_components->emplace_back(new Movable(this, 80));
	m_components->emplace_back(new HitBox(this, 15, 8, -4));
}

Bullet::Bullet(float x, float y, float angle, float lifespan) : Bullet( SDL_Sprite::Load(0, 0, 8, 15, "bullet.png"), x, y, angle, lifespan)
{
}

Bullet::~Bullet()
{
}


void Bullet::Update()
{
	if (!Active)
		return;
	Entity::Update();
	Movable* moveComponent = (Movable*)GetComponent("movable");
	moveComponent->Move(Angle);
	
	LifeSpan -= TimeController::instance.DeltaTime;
	
	if (LifeSpan <= 0)
		SetIsDying(true);

	if (GetIsDying())
	{
		IScene::m_entities->push_back(new Explosion(this->X, this->Y));
		Active = false;
	}
}

void Bullet::Draw()
{
	m_sprite->Draw(Globals::Renderer, X, Y, Angle+90);
	for (auto& component : *m_components)
	{
		component->Draw();
	}
}
