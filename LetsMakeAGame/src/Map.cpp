
#include "Map.h"
#include "IScene.h"
#include "Tank.h"
#include <iostream>

Map::Map(int width, int height) : m_width(width), m_height(height)
{
	data = new MapSpot*[height];
	for (int i = 0; i < height; i++)
	{
		data[i] = new MapSpot[width];
	}
}

Map::~Map()
{
	for (int i = 0; i < m_height; i++)
		delete[] data[i];

	delete[] data;
}

void Map::Reset()
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
			data[i][j] = MapSpot();
	}
}

void Map::ResetChecked()
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
			data[i][j].Checked = false;
	}

}

void Map::Print()
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
			std::cout << data[i][j].GridType << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

}

std::list<SDL_Point> *Map::FindDirection(SDL_Point startLoc, SDL_Point endpoint)
{
	ResetHiristic();
	bool madeIt;
	SDL_Point reducedStartLoc = MathHelper::ReducePoint(startLoc);
	SDL_Point reducedEndPoint = MathHelper::ReducePoint(endpoint);
	MapSpot * firstItem = &data[reducedStartLoc.y][reducedStartLoc.x];
	firstItem->Checked = true;
	firstItem->Direction = SDL_Point();
	MapSpot item = AStar(data[reducedStartLoc.y][reducedStartLoc.x], reducedEndPoint);

	if (item.FCost == INT32_MAX)
		return new std::list<SDL_Point>();

	std::list<SDL_Point> *moveDirections = new std::list<SDL_Point>();
	while (item.Direction.x != 0 || item.Direction.y != 0) {
		moveDirections->emplace_back(item.Direction);
		item = data[item.Loc.y + item.Direction.y][item.Loc.x + item.Direction.x];
	}

	return moveDirections;
}

SDL_Point Map::LocateObject(SDL_Point myLoc)
{
	bool noOpen;
	SDL_Point whereAt = MathHelper::CreatePoint(-1, -1);
	float fardist = 0;
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			if (data[i][j].GridType == GridType::tank)
			{
				SDL_Point p;
				p.x = j * 32;
				p.y = i * 32;
				float dist = MathHelper::DistanceBetweenTwoPoints(&p, &myLoc);
				if (dist > fardist)
				{
					whereAt = p;
					fardist = dist;
					noOpen = true;
				}
			}
		}
	}
	return whereAt;
}

bool Map::SomethingInbetween(SDL_Point startLoc, SDL_Point other)
{
	SDL_Point loc = startLoc;
	loc.x /= 32;
	loc.y /= 32;
	SDL_Point a = other;
	a.x /= 32;
	a.y /= 32;
	float dist = 0;
	float x, y;
	SDL_Point whole = startLoc;
	float angle = MathHelper::AngleBetweenTwoPoints(startLoc.x, startLoc.y, other.x, other.y);
	x = sin(angle);
	y = cos(angle);
	int i = 1;
	do {
		whole.x = loc.x + x * i;
		whole.y = loc.y + y * i;
		if (data[whole.y][whole.x].GridType == GridType::dirtwall || data[whole.y][whole.x].GridType == GridType::wall)
			return true;
	} while (whole.x == other.x && whole.y == whole.y);

	return false;
}

void Map::PopulateMap()
{
	Reset();
	for (auto entity : *IScene::m_entities)
	{
		if (!entity->Active)
			continue;
		if (entity->GetType() == "tank" && !((Tank*)entity)->IsAlive())
			continue;

		SDL_Point other;
		other.x = (entity->X) / 32;
		other.y = (entity->Y) / 32;
		SetMap(other, entity->GetType());
	}
}

void Map::ResetHiristic()
{
	for (int i = 0; i < m_height; i++)
		for (int j = 0; j < m_width; j++)
			data[i][j].ResetHiristic(j, i);
}

GridType Map::BStar(SDL_Point currentLoc, SDL_Point startLoc, int maxDist)
{
	const int maxDistSquared = maxDist * maxDist;
	if (currentLoc.x < 0 || currentLoc.x >= m_width || currentLoc.y < 0 || currentLoc.y >= m_height)
		return GridType::unsolved;

	if (data[currentLoc.y][currentLoc.x].Checked)
		return data[currentLoc.y][currentLoc.x].GridType;

	if (MathHelper::DistanceBetweenTwoPoints(&startLoc, &currentLoc) >= maxDistSquared)
		return GridType::unsolved;

	data[currentLoc.y][currentLoc.x].Checked = true;

	if (data[currentLoc.y][currentLoc.x].GridType == GridType::open) {
		return GridType::open;
	}
	else {
		float angle = MathHelper::AngleBetweenTwoPointsR(startLoc, currentLoc);

		if (AnythingInLine(MathHelper::CreatePoint(currentLoc.x, currentLoc.y), startLoc, angle))
			return GridType::unsolved;

		return data[currentLoc.y][currentLoc.x].GridType;
	}
}

bool Map::AnythingInLine(SDL_Point currentLoc, SDL_Point startLoc, float angle)
{
	float sinangle = sin(angle);
	float cosangle = cos(angle);
	int rounds = 1;
	SDL_Point c = currentLoc;
	while (!(c.x == startLoc.x && c.y == startLoc.y))
	{
		c.x = currentLoc.x - round(rounds * cosangle);
		c.y = currentLoc.y - round(rounds * sinangle);

		if (c.x == startLoc.x && c.y == startLoc.y)
			break;

		if (data[c.y][c.x].GridType != GridType::unsolved && data[c.y][c.x].GridType != GridType::open)
		{
			return true;
		}
		rounds++;
	}

	return false;
}

int Map::Round(float number)
{
	if (number > .707)
		return 1;
	if (number < -.707)
		return -1;

	return 0;
}

std::list<GridEntity> Map::FindAllObjectsNear(SDL_Point startLoc, int maxDist)
{
	ResetChecked();
	std::list<GridEntity> entities;
	for (int i = -maxDist; i < maxDist; i++)
	{
		for (int j = -maxDist; j < maxDist; j++)
		{

			SDL_Point loc = MathHelper::CreatePoint(startLoc.x + j, startLoc.y + i);
			if (loc.x == startLoc.x && loc.y == startLoc.y)
				continue;

			GridType gridType = BStar(loc, startLoc, maxDist);
			if (gridType == GridType::wall || gridType == GridType::dirtwall || gridType == GridType::tank) {
				GridEntity gridentity = GridEntity();
				gridentity.gridType = gridType;
				gridentity.loc = loc;
				gridentity.angle = MathHelper::AngleBetweenTwoPoints(startLoc.x, startLoc.y, loc.x, loc.y);
				entities.push_back(gridentity);
			}
		}
	}

	return entities;
}


MapSpot Map::AStar(MapSpot item, SDL_Point endLoc)
{
	if (item.Loc.x == endLoc.x && item.Loc.y == endLoc.y)
		return item;

	//Calculate FCost
	for (int i = item.Loc.y - 1; i <= item.Loc.y + 1; i++)
	{
		if (i < 0 || i >= m_height)
			continue;
		for (int j = item.Loc.x - 1; j <= item.Loc.x + 1; j++)
		{
			if (j < 0 || j >= m_width || data[i][j].Checked || (i == item.Loc.y && j == item.Loc.x) || data[i][j].GridType == GridType::wall)
				continue;
			if ((i == item.Loc.y) ^ (j == item.Loc.x))
			{
				MapSpot nextItem;
				nextItem.Loc.x = j;
				nextItem.Loc.y = i;
				nextItem.HCost = 10 + item.HCost;
				nextItem.GCost = MathHelper::DistanceBetweenTwoPoints(&endLoc, &MathHelper::CreatePoint(i, j));
				nextItem.CalcFCost();
				nextItem.Direction = MathHelper::CreatePoint(item.Loc.x - j, item.Loc.y - i);

				if (nextItem.FCost <= data[i][j].FCost)
					data[i][j] = nextItem;
			}
		}
	}

	int lowestfCost = INT32_MAX;
	MapSpot* lowestHir = nullptr;
	bool foundSpot = false;
	//Find lowest FCost
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			if (!data[i][j].Checked && data[i][j].FCost != INT32_MAX && (lowestfCost >= data[i][j].FCost || (lowestfCost == data[i][j].FCost)))
			{
				lowestHir = &data[i][j];
				lowestfCost = lowestHir->FCost;
				foundSpot = true;
			}
		}
	}
	if (foundSpot && lowestHir != nullptr) {
		lowestHir->Checked = true;
		return AStar(*lowestHir, endLoc);
	}
	return MapSpot();
}

void Map::SetMap(SDL_Point point, std::string type)
{
	if (point.x < 0 || point.x >= m_width || point.y < 0 || point.y >= m_height)
		return;
	GridType part;
	if (type == "wall")
		part = GridType::wall;
	else if (type == "dirtwall")
		part = GridType::dirtwall;
	else if (type == "tank")
		part = GridType::tank;
	else if (type == "powerup" && data[point.y][point.x].GridType != GridType::dirtwall)
		part = GridType::powerup;
	else
		part = data[point.y][point.x].GridType;

	data[point.y][point.x].GridType = part;

}
