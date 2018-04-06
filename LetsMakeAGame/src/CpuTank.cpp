#include "CpuTank.h"

CpuTank::CpuTank(float x, float y, int playernumber,  Map * map) : Tank(x, y, playernumber)
{
	timeInCurrentMode = .51;
	justfired = 0;

	mode = AiMode::Sleep;
	m_map = map;
}

CpuTank::~CpuTank()
{
}

bool CpuTank::ShouldFire()
{
	int action = 0;
	std::list<GridEntity> items = FindInFrontDirtWalls();
	if (items.size() == 0)
		return false;

	if (rand() % 3 == 0) {
		//has tank, fire at it
		for (auto entity : items)
		{
			if (entity.gridType == GridType::tank) {
				moveDirection = entity.angle;
				return true;
			}
		}
	}

	int dirtCount = 0;
	for (auto entity : items)
	{
		if (entity.gridType == GridType::dirtwall)
			dirtCount++;
	}
	if (dirtCount == 0)
		return false;

	int whichDirt = rand() % dirtCount;

	SDL_Point myLoc = MathHelper::CreatePoint(X / 32, Y / 32);
	int count = 0;
	//has dirt wall, fire at that
	for (auto entity : items)
	{
		float dist = MathHelper::DistanceBetweenTwoPoints(&entity.loc, &myLoc);
		if (entity.gridType == GridType::dirtwall &&  dist > 4.1) {
			if (count++ == whichDirt) {
				moveDirection = entity.angle;
				return true;
			}
		}
	}

	return false;
}

std::list<GridEntity> CpuTank::FindInFrontDirtWalls()
{
	std::list<GridEntity> items = m_map->FindAllObjectsNear(MathHelper::CreatePoint((X / 32), (Y / 32)), 5);

	for (auto item = items.begin(); item != items.end();)
	{
		if (item->gridType == GridType::wall)
			item = items.erase(item);
		else
			item++;
	}

	return items;
}


void CpuTank::Update()
{
	if (justfired > 0)
		justfired -= TimeController::instance.DeltaTime;
	if (timeInCurrentMode > 0)
		timeInCurrentMode -= TimeController::instance.DeltaTime;
	//if (calculateMovesAgain > 0)
	//	calculateMovesAgain -= TimeController::instance.DeltaTime;

	Tank::Update();

	if (timeInCurrentMode <= 0) {
		if (!TryFire() && !TryMove())
		{
			mode = AiMode::Sleep;
		}
		else
			timeInCurrentMode = .8;
	}
	else {
		float dist;
		switch (mode)
		{
		case  AiMode::Move:
			dist = MathHelper::DistanceBetweenTwoPoints(&startloc, &MathHelper::CreatePoint(X, Y));
			if (dist > 1024)
				timeInCurrentMode = 0;
			Move();
			break;
		case  AiMode::Fire:
			Fire();
			break;
		case  AiMode::Sleep:
			break;
		}
	}
}

bool CpuTank::TryFire()
{
	bool shouldFire = ShouldFire();
	if (shouldFire)
	{
		mode = AiMode::Fire;
		Fire();
		return true;
	}
	return false;
}


bool CpuTank::TryMove()
{
	if (calculateMovesAgain <= 0)
	{
		if (moveDirections != nullptr) {
			while (!moveDirections->empty()) {
				moveDirections->pop_back();
			}
			delete moveDirections;
		}
		SDL_Point other = m_map->LocateObject(MathHelper::CreatePoint(X, Y));
		moveDirections = m_map->FindDirection(MathHelper::CreatePoint(X, Y), other);
		calculateMovesAgain = 5;
	}
	else {

		if (moveDirections->empty()) {
			calculateMovesAgain = 0;
			return false;
		}
		else {
			startloc = MathHelper::CreatePoint(X, Y);
			SDL_Point dir = moveDirections->back();
			moveDirections->pop_back();

			moveDirection = atan2(-dir.y, -dir.x) * 180 / M_PI;
			mode = AiMode::Move;
			return true;
		}
	}
}

void CpuTank::Move()
{
	PerformMove(moveDirection, .99999);
}

void CpuTank::Fire()
{
	if (justfired > 0) {
		mode = AiMode::Sleep;
		return;
	}
	PerformMove(moveDirection, .001);
	PerformAction(Action::Fire);
	mode = AiMode::Sleep;
	justfired = 1.5;
	timeInCurrentMode = 1;
}

