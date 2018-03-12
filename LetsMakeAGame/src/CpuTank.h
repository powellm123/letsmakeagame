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
	DecisionTree* tree;
public:
	CpuTank(float x, float y, int playernumber, Buttons *buttons, SDL_Sprite *sprite, Map *map);
	~CpuTank();
	void Update() override;

	static bool IsNextTo(SDL_Point *point, Entity* object);
	static bool IsLoc(SDL_Point* point, SDL_Point* other);
private:
	bool TryFire();
	bool TryMove();
	void Move();
	void Fire();

	int Round(float number);

	std::list<GridEntity> FindInFrontDirtWalls();
	bool ShouldFire();

};