#include "Bullet.h"
#include "Movable.h"
#include "HitBox.h"
#include "Explosion.h"
#include "SpriteManager.h"
#include "SpriteFactory.h"

Bullet::Bullet(float x, float y, float angle, float lifespan, int size) : Bullet(x, y, angle, lifespan, size,SpriteFactory::GetSprite("bullet", 1))
{
}

Bullet::Bullet(float x, float y, float angle, float lifespan, int size, Sprite * sprite) : Entity(type, 0, 0, sprite), m_size(size)
{
	static const float dtr = M_PI / 180;
	this->X = x + cos(angle*dtr) * 45;
	this->Y = y + sin(angle*dtr) * 45;
	this->Angle = angle;
	this->Active = true;

	LifeSpan = lifespan;

	m_components->emplace_back(new Movable(this, 80));
	m_components->emplace_back(new HitBox(this, 15, 8, -4));
}


Bullet::~Bullet()
{
}


void Bullet::Update()
{
	if (!Active)
		return;
	Entity::Update();
	Movable* moveComponent = (Movable*)GetComponent(Movable::type);
	moveComponent->Move(Angle);
	
	LifeSpan -= TimeController::instance.DeltaTime;
	
	if (LifeSpan <= 0)
		SetIsDying(true);

	if (GetIsDying())
	{
		IScene::m_entities->push_back(new Explosion(this->X, this->Y, m_size));
		Active = false;
	}
}

void Bullet::Draw()
{
	m_sprite->Draw(MathHelper::CreatePoint( X, Y), Angle+90, 1,1);
	for (auto& component : *m_components)
	{
		component->Draw();
	}
}
