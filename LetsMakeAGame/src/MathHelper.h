#pragma once

#include <SDL.h>
#include <list>
class Entity;

class MathHelper
{
public:
	//Helper
	static float DistanceBetweenTwoPoints(SDL_Point *p, SDL_Point* e);
	static float DistanceBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2);
	static float DistanceBetweenTwoEntities(Entity *entity1, Entity *entity2);
	static float DistanceBetweenTwoEntitiesBy32(Entity *entity1, Entity* entity2);
	static float DistanceBetweenPointAndEntity(SDL_Point *p, Entity* e);
	static float AngleBetweenPointAndEntities(SDL_Point *p, Entity *e);
	static float AngleBetweenTwoEntities(Entity *entity1, Entity *entity2);
	static bool CheckCollision(SDL_Rect &rect1, SDL_Rect &rect2);
	static float AngleBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2);
	static float AngleBetweenTwoPointsR(SDL_Point c1, SDL_Point c2);
	static float AngleBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2);

	static SDL_Point CreatePoint(int x, int y);
	static SDL_Point ReducePoint(SDL_Point p);

	static bool EntityCompare(const Entity* const &a, const Entity* const &b);
	static void RemoveInactiveEntitiesFromList(std::list<Entity*> *entities, bool deleteEntities);
	static void RemoveAllFromList(std::list<Entity*> *entities, bool deleteEntities);
};