#pragma once

#include "Tank.h"
#include "Map.h"
#include "DecisionTree.h"

enum class AiMode { Move, Fire, RandomMove, Locate_Object, Locate_Player, MoveDirection, Sleep };
enum FaceDirection { Up, Left, Down, Right };

class CpuTank : public Tank
{
	AiMode mode;
	float timeInCurrentMode;
	float moveDirection;
	float calculateMovesAgain;
	float justfired;
	SDL_Point startloc;
	std::list<SDL_Point>* moveDirections;
	Map * m_map;
public:
	CpuTank(float x, float y, int playernumber, Buttons *buttons, Map *map);
	virtual ~CpuTank();
	void Update() override;

private:
	bool TryFire();
	bool TryMove();
	void Move();
	void Fire();


	std::list<GridEntity> FindInFrontDirtWalls();
	bool ShouldFire();

};