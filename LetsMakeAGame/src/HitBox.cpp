#include "HitBox.h"
#include "Entity.h"
#include "Movable.h"
#include "PowerUp.h"
#include "Tank.h"

HitBox::HitBox(Entity * actor, int collisionBoxWidth, int collisionBoxHeight, int collisionBoxYOffset, bool isStaticHitbox)
	: IComponent(actor, "hitbox"), CollisionBoxWidth(collisionBoxWidth), CollisionBoxHeight(collisionBoxHeight), CollisionBoxYOffset(collisionBoxYOffset), m_isStaticHitBox(isStaticHitbox)
{
}

void HitBox::Update()
{
	UpdateCollisionBox();
	
	LastCollisionBox = CollisionBox;
	UpdateCollisions();
}

void HitBox::Draw()
{
	
	if ( Globals::Debugging)
	{
		SDL_SetRenderDrawColor(Globals::Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::Renderer, &CollisionBox);
	}

}

void HitBox::UpdateCollisionBox()
{

	CollisionBox.x = m_actor->X - CollisionBox.w / 2;
	CollisionBox.y = m_actor->Y + CollisionBoxYOffset;
	CollisionBox.w = CollisionBoxWidth;
	CollisionBox.h = CollisionBoxHeight;
}

void HitBox::UpdateCollisions()
{

	if (!m_actor->Active || m_isStaticHitBox)
		return;

	if (m_actor->GetType() == "tank" && !((Player*)m_actor)->IsAlive())
		return;


	//list of potential collisions
	list<Entity*> collisions;

	for (auto it = IScene::m_entities->begin(); it != IScene::m_entities->end(); it++)
	{
		HitBox* hitboxcomp = (HitBox*)(*it)->GetComponent("hitbox");
		if (hitboxcomp == nullptr)
			continue;
		if ((*it)->Active && (*it)->GetId() != m_actor->GetId()
			&& CheckCollision(CollisionBox, hitboxcomp->CollisionBox))
		{
			collisions.push_back((*it));
		}
	}

	if (collisions.size() == 0)
		return;

	UpdateCollisionBox();

	float boxTravelSize = 0;
	if (CollisionBox.w < CollisionBox.h)
		boxTravelSize = CollisionBox.w / 4;
	else
		boxTravelSize = CollisionBox.h / 4;

	SDL_Rect samplebox = LastCollisionBox;
	float movementAngle = HitBox::AngleBetweenTwoRects(LastCollisionBox, CollisionBox);

	bool foundCollision = false;
	
	SDL_Rect intersection;
	for (auto collision : collisions)
	{
		if (m_actor->GetIsDying())
			break;
		if (!collision->Active )
			continue;
		SDL_Rect theirCollisionBox = ((HitBox*)collision->GetComponent("hitbox"))->CollisionBox;
		//Check sample box for collisions where it is now
		if (SDL_IntersectRect(&CollisionBox, &theirCollisionBox, &intersection))
		{
			foundCollision = true;

			std::string collisionType = collision->GetType();
			std::string actorType = m_actor->GetType();

			if (collisionType == actorType && actorType == "tank")
			{
				if (((Player*)collision)->IsAlive())
				{
					Movable* comp = (Movable*)m_actor->GetComponent("movable");
					comp->Move(HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, collision->X, collision->Y) - 180);
				}
			}

			else {
				if (collisionType == actorType && actorType == "bullet")
				{
					m_actor->SetIsDying(true);
				}

				else {
					if (collisionType != actorType && actorType == "tank")
					{
						if (collisionType == "bullet")
						{
							collision->SetIsDying(true);
							Movable* comp = (Movable*)m_actor->GetComponent("movable");
							comp->Move(HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, collision->X, collision->Y) - 180, 5);
							((Tank*)m_actor)->DoDamage(1);
						}

						if (collisionType == "explosion")
						{
							Movable* comp = (Movable*)m_actor->GetComponent("movable");
							comp->Move(HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, collision->X, collision->Y) - 180, 5);
							((Tank*)m_actor)->DoDamage(1);
						}

						if (collisionType == "wall" || collision->GetType() == "dirtwall" )
						{
							Movable* comp = (Movable*)m_actor->GetComponent("movable");

							float angle = HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, collision->X, collision->Y);
							int pow = comp->GetMoveSpeed();
							if (pow >= 0)
								comp->CollidedWithSolid(angle);
							else
								comp->CollidedWithSolid(angle - 180);
						}
						if ( collision->GetType() == "boarder")
						{
							Movable* comp = (Movable*)m_actor->GetComponent("movable");
							float angle = 0;
							if(abs(m_actor->X - collision->X) > abs(m_actor->Y - collision->Y))
								angle = HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, m_actor->X, collision->Y);
							else
								angle = HitBox::AngleBetweenTwoPoints(m_actor->X, m_actor->Y, collision->X, m_actor->Y);
							int pow = comp->GetMoveSpeed();
							if (pow >= 0)
								comp->CollidedWithSolid(angle);
							else
								comp->CollidedWithSolid(angle-180);

						}
						else if (collisionType == "powerup")
						{
							PowerUp* p = (PowerUp*)collision;
							collision->SetIsDying(true);
							//collision->Active = false;
							((Tank*)m_actor)->AddPowerUp(p);
						}
					}

					else {
						if (collisionType != actorType && actorType == "bullet")
						{
							if (collisionType == "wall" || collisionType == "explosion" || collision->GetType() == "boarder")
							{
								m_actor->SetIsDying(true);
							}
							if (collisionType == "dirtwall")
							{
								m_actor->SetIsDying(true);
								HealthComponent* comp = (HealthComponent*)collision->GetComponent("health");
								comp->Damage(1);
							}
						}
						if (collisionType != actorType && actorType == "explosion")
						{
							if (collisionType == "dirtwall")
							{
								HealthComponent* comp = (HealthComponent*)collision->GetComponent("health");
								comp->Damage(1);
							}
						}
					}
				}
			}
		}


		samplebox = CollisionBox;
	}

	if (foundCollision)
	{
		//move our entity to where the samplebox ended up
		//SlideAmount = SlideAmount / 2;
		//m_actor->x += samplebox.x + samplebox.w / 2;
		//m_actor->y += samplebox.y - CollisionBoxYOffset;

		
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
