#include "HitBox.h"
#include "Entity.h"
#include "Movable.h"
#include "PowerUp.h"
#include "Tank.h"
#include "DirtWall.h"
#include "Boarder.h"
#include "Explosion.h"
#include "Wall.h"

HitBox::HitBox(Entity * actor, int collisionBoxWidth, int collisionBoxHeight, int collisionBoxYOffset, bool isStaticHitbox)
	: IComponent(actor, "hitbox", type), CollisionBoxWidth(collisionBoxWidth), CollisionBoxHeight(collisionBoxHeight), CollisionBoxYOffset(collisionBoxYOffset), m_isStaticHitBox(isStaticHitbox)
{
	UpdateCollisionBox();
}

void HitBox::Update()
{
	UpdateCollisions();
}

void HitBox::Draw()
{
	if (Globals::Debugging)
	{
		SDL_SetRenderDrawColor(Globals::Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::Renderer, &CollisionBox);
	}
}

void HitBox::UpdateCollisionBox()
{
	CollisionBox.x = m_actor->X;// -CollisionBox.w / 2;
	CollisionBox.y = m_actor->Y;// -CollisionBox.h / 2;
	CollisionBox.w = CollisionBoxWidth;
	CollisionBox.h = CollisionBoxHeight;
}

void HitBox::UpdateCollisions()
{
	UpdateCollisionBox();
	if (!m_actor->Active || m_isStaticHitBox)
		return;

	if (m_actor->GetType() == Tank::type && !((Player*)m_actor)->IsAlive())
		return;


	//list of potential collisions
	list<Entity*> collisions;


	for (auto it : *IScene::m_entities)
	{
		HitBox* hitboxcomp = (HitBox*)(it)->GetComponent(HitBox::type);
		if (hitboxcomp == nullptr)
			continue;

		if ((it)->Active && (it)->GetId() != m_actor->GetId()
			&& CheckCollision(CollisionBox, hitboxcomp->CollisionBox))
		{
			collisions.push_back((it));
		}
	}

	if (collisions.size() == 0)
		return;


	SDL_Rect intersection;
	for (auto collision : collisions)
	{
		if (m_actor->GetIsDying())
			break;
		if (!collision->Active)
			continue;
		SDL_Rect theirCollisionBox = ((HitBox*)collision->GetComponent(HitBox::type))->CollisionBox;
		//Check sample box for collisions where it is now
		if (SDL_IntersectRect(&CollisionBox, &theirCollisionBox, &intersection))
		{
			size_t collisionType = collision->GetType();
			size_t actorType = m_actor->GetType();

			if (actorType == Tank::type)
			{
				float angle;
				int pow;
				Movable* comp = (Movable*)m_actor->GetComponent(Movable::type);
				switch (collisionType)
				{
				case Tank::type:
					if (((Player*)collision)->IsAlive()) {
						comp->Move(HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, collision->X, collision->Y) - 180);
					}
					break;
				case Bullet::type:
					collision->SetIsDying(true);
					comp->Move(HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, collision->X, collision->Y), -11);
					((Tank*)m_actor)->DoDamage(1);
					break;
				case Explosion::type:
					comp->Move(HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, collision->X, collision->Y) , -11);
					((Tank*)m_actor)->DoDamage(1);
					break;
				case DirtWall::type:
				case Wall::type:
					angle = HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, collision->X, collision->Y);
					pow = comp->GetMoveSpeed();
					if (pow >= 0)
						comp->CollidedWithSolid(angle);
					else
						comp->CollidedWithSolid(angle - 180);
					break;
				case Boarder::type:
					angle = 0;
					if (abs(m_actor->X - collision->X) > abs(m_actor->Y - collision->Y))
						angle = HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, m_actor->X, collision->Y);
					else
						angle = HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, collision->X, m_actor->Y);
					pow = comp->GetMoveSpeed();
					if (pow >= 0)
						comp->CollidedWithSolid(angle);
					else
						comp->CollidedWithSolid(angle - 180);
					break;
				case PowerUp::type:
					PowerUp * p = (PowerUp*)collision;
					collision->SetIsDying(true);
					((Tank*)m_actor)->AddPowerUp(p);
					break;
				}
			}
			else if (actorType == Bullet::type)
			{
				switch (collisionType)
				{
				case Bullet::type:
					m_actor->SetIsDying(true);
					break;
				case Wall::type:
				case Explosion::type:
				case Boarder::type:
					m_actor->SetIsDying(true);
					break;
				case DirtWall::type:
					m_actor->SetIsDying(true);
					HealthComponent* comp = (HealthComponent*)collision->GetComponent(HealthComponent::type);
					comp->Damage(1);
					break;
				}
			}
			else if (actorType == Explosion::type && collisionType == DirtWall::type)
			{
				HealthComponent* comp = (HealthComponent*)collision->GetComponent(HealthComponent::type);
				comp->Damage(1);
			}
		}
	}
	UpdateCollisionBox();
}

bool HitBox::CheckCollision(SDL_Rect & rect1, SDL_Rect & rect2)
{
	SDL_Rect intersection;
	if (SDL_IntersectRect(&rect1, &rect2, &intersection))
	{
		return true;
	}
	return false;
}



//Helper
float HitBox::DistanceBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2)
{
	SDL_Point e1, e2;
	e1.x = rect1.x + rect1.w / 2;
	e1.y = rect1.y + rect1.h / 2;

	e2.x = rect2.x + rect2.w / 2;
	e2.y = rect2.y + rect2.h / 2;

	float d = abs(sqrt(pow(e2.x - e1.x, 2) + pow(e2.y - e1.y, 2)));
	return d;
}

float HitBox::AngleBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2)
{
	float dx = cx2 - cx1;
	float dy = cy2 - cy1;

	return atan2(dy, dx) * 57.295779513;
}

float HitBox::AngleBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2)
{
	float cx1 = rect1.x + rect1.w / 2;
	float cy1 = rect1.y + rect1.h / 2;

	float cx2 = rect2.x + rect2.w / 2;
	float cy2 = rect2.y + rect2.h / 2;

	return AngleBetweenTwoPoints(cx1, cy1, cx2, cy2);
}
