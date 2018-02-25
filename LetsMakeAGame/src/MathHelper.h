#pragma once

#include <SDL.h>
#include <list>
class Entity;

class MathHeler
{
public:
	//Helper
	static float DistanceBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2);
	static float DistanceBetweenTwoEntities(Entity *entity1, Entity *entity2);
	static float AngleBetweenTwoEntities(Entity *entity1, Entity *entity2);
	static bool CheckCollision(SDL_Rect &rect1, SDL_Rect &rect2);
	static float AngleBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2);
	static float AngleBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2);

	static bool EntityCompare(const Entity* const &a, const Entity* const &b);
	static void RemoveInactiveEntitiesFromList(std::list<Entity*> *entities, bool deleteEntities);
	static void RemoveAllFromList(std::list<Entity*> *entities, bool deleteEntities);
};