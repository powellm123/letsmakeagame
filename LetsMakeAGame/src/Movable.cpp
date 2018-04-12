
#include "Movable.h"
#include "Entity.h"


Movable::Movable(Entity* actor, int maxMoveSpeed, int moveLerp) : IComponent(actor, "movable", type)
{
	MaxMoveSpeed = UseMoveSpeed = maxMoveSpeed;
	MoveLerp = moveLerp;
}

void Movable::Update()
{
	//reset total moves
	TotalXMove = 0;
	TotalYMove = 0;

	if (abs(MoveSpeed) > 0.0001)
	{
		float moveDist = MoveSpeed * (TimeController::instance.DeltaTime) * MoveLerp;
		if (abs(moveDist) > 0.0001)
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

			if (abs(MoveSpeed) >= 0.0001)
				MoveSpeed -= moveDist;
		}
	}

	while (!SolidsDirections.empty())
	{
		SolidsDirections.pop_back();
	}
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

void Movable::Rotate(float angle)
{
	Angle += angle;
}

void Movable::Move()
{
	IsMoving = true;
	MoveSpeed = 1;
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

void Movable::SetAngle(double angle)
{
	Angle = angle;
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
	SpeedUpCount = SpeedUpCount < 7 ? SpeedUpCount + 1: SpeedUpCount;
	float speedIncrease = MaxMoveSpeed * SpeedUpCount * .11;
	UseMoveSpeed = MaxMoveSpeed + speedIncrease;
}

float Movable::GetUseMoveSpeed()
{
	return UseMoveSpeed;
}
