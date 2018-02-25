
#include "Movable.h"
#include "Entity.h"


Movable::Movable(Entity* actor, int maxMoveSpeed) : IComponent(actor, "movable") 
{
	MaxMoveSpeed = UseMoveSpeed = maxMoveSpeed;
	MoveLerp = 4;
}

void Movable::Update()
{
	//UpdateCollisionBox();
	//store collisionbox before we move
	//LastCollisionBox = CollisionBox;

	//reset total moves
	TotalXMove = 0;
	TotalYMove = 0;

	if (abs(MoveSpeed) > 0.000001)
	{
		float moveDist = MoveSpeed * (TimeController::instance.DeltaTime) * MoveLerp;
		if (abs(moveDist) > 0.000001)
		{
			float xangle = 0;
			float yangle = 0;
			for (auto& v : SolidsDirections)
			{
				xangle += std::cos((v-180) * M_PI / 180);
				yangle += std::sin((v - 180) * M_PI / 180);
			}

			float xMove = std::cos(Angle * M_PI / 180);
			float yMove = std::sin(Angle * M_PI / 180);


			m_actor->X += moveDist *( xMove + xangle);
			m_actor->Y += moveDist * (yMove + yangle);

			TotalXMove = xMove;
			TotalYMove = yMove;

			if (abs(MoveSpeed) >= 0.0000001)
				MoveSpeed -= moveDist;
		}
	}

	while (!SolidsDirections.empty())
	{
		SolidsDirections.pop_back();
	}

	//if (SlideAmount > 0)
	//{
	//	float slideDist = SlideAmount * TimeController::instance.DeltaTime * MoveLerp;
	//	if (slideDist > 0) {
	//		float xMove = slideDist * cos(SlideAngle * M_PI / 180);
	//		float yMove = slideDist * sin(SlideAngle * M_PI / 180);

	//		m_actor->x += xMove;
	//		m_actor->y += yMove;

	//		TotalXMove += xMove;
	//		TotalYMove += yMove;

	//		SlideAmount -= slideDist;
	//	}
	//	else
	//	{
	//		SlideAmount = 0;
	//	}
	//}
	// now that we've moved, move the collisionbox up to where we are now
	//UpdateCollisionBox();
	//to help with collision checking, union colisionBox with lastCollisionBox
	//SDL_UnionRect(&CollisionBox, &LastCollisionBox, &CollisionBox);
	
}

void Movable::Draw()
{
}

void Movable::Move(float angle)
{
	IsMoving = true;
	if (MoveSpeed < UseMoveSpeed)
		MoveSpeed += UseMoveSpeed;
	Angle = angle;
}

void Movable::Move(float angle, double power)
{
	IsMoving = true;
	if (abs(power) < UseMoveSpeed)
		MoveSpeed = power;
	Angle = angle;
}

void Movable::CollidedWithSolid(double angle)
{
	SolidsDirections.emplace_back(angle);
}

double Movable::GetMoveSpeed()
{
	return MoveSpeed;
}

Movable::MoveState Movable::GetMoveState()
{
	return State;
}

void Movable::SetIsMoving(bool isMoving)
{
	IsMoving = isMoving;
}

double Movable::GetAngle()
{
	return Angle;
}

void Movable::SetMoveSpeed(int newMoveSpeed)
{
	MoveSpeed = newMoveSpeed;
}

void Movable::IncreaseMaxSpeed()
{
	SpeedUpCount = SpeedUpCount < 9 ? SpeedUpCount + 1: SpeedUpCount;
	float speedIncrease = MaxMoveSpeed * SpeedUpCount * .1;
	UseMoveSpeed = MaxMoveSpeed + speedIncrease;
}

float Movable::GetUseMoveSpeed()
{
	return UseMoveSpeed;
}


