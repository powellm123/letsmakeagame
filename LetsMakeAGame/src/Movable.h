#pragma once

#include <iostream>
#include "IComponent.h"
#include "TimeController.h"
#include "MathHelper.h"


class Movable : public IComponent
{
public:
	//reference constants
	//static const enum DirectionState { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, NONE = 0 };
	static const enum class MoveState {MOVE, IDEL, DEAD};
	Movable(Entity* actor, int maxMoveSpeed);
	void Update() override;
	void Draw() override;
	void Move(float angle);
	void Move(float angle, double power);
	double GetMoveSpeed();
	MoveState GetMoveState();
	void SetIsMoving(bool isMoving);
	double GetAngle();
	void SetMoveSpeed(int newMoveSpeed);
	void IncreaseMaxSpeed();
	float GetUseMoveSpeed();
	void CollidedWithSolid(double angle);
	//static DirectionState AngleToDirection(float angle);
	
protected:
	//DirectionState Direction;
	MoveState State;
	bool IsMoving;
	double MoveSpeed;
	double UseMoveSpeed;
	double MaxMoveSpeed;
	int SpeedUpCount;
	double Angle;
	float MoveLerp;
	int TotalXMove;
	int TotalYMove;
	int SlideAmount;
	float SlideAngle;
	std::list<double> SolidsDirections;
};