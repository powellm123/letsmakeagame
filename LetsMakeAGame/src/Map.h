#pragma once

#include "MapSpot.h"
#include "GridEntity.h"

class Map
{
	MapSpot **data;
	int m_width;
	int m_height;
public:
	Map(int width, int height);
	~Map();
	void Reset();
	void ResetChecked();
	void Print();
	std::list<SDL_Point>* FindDirection(SDL_Point startLoc, SDL_Point endpoint);
	std::list<GridEntity> FindAllObjectsNear(SDL_Point startLoc, int maxDist);
	GridType BStar(SDL_Point currentLoc, SDL_Point startLoc, int maxDist);
	SDL_Point LocateObject(SDL_Point myLoc);
	void PopulateMap();
	bool SomethingInbetween(SDL_Point startLoc, SDL_Point other);

	bool AnythingInLine(SDL_Point currentLoc, SDL_Point startLoc, float angle);
	static int Round(float number);

private:
	void ResetHiristic();
	MapSpot AStar(MapSpot item, SDL_Point endLoc);
	void SetMap(SDL_Point point, size_t type);
};