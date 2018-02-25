
#include "Entity.h"
#include "MathHelper.h"

//Helper
float MathHeler::DistanceBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2)
{
	SDL_Point e1, e2;
	e1.x = rect1.x + rect1.w / 2;
	e1.y = rect1.y + rect1.h / 2;

	e2.x = rect2.x + rect2.w / 2;
	e2.y = rect2.y + rect2.h / 2;

	float d = abs(sqrt(pow(e2.x - e1.x, 2) + pow(e2.y - e1.y, 2)));
	return d;
}
float MathHeler::DistanceBetweenTwoEntities(Entity *e1, Entity *e2)
{
	return abs(sqrt(pow(e2->X - e1->X, 2) + pow(e2->Y - e1->Y, 2)));
}

float MathHeler::AngleBetweenTwoEntities(Entity *e1, Entity *e2)
{
	float dx, dy;
	float x1 = e1->X, y1 = e1->Y, x2 = e2->X, y2 = e2->Y;

	dx = x2 - x1;
	dy = y2 - y1;

	return atan2(dy, dx) * 180 / M_PI;
}
bool MathHeler::CheckCollision(SDL_Rect &rect1, SDL_Rect &rect2)
{
	SDL_Rect intersection;
	if (SDL_IntersectRect(&rect1, &rect2, &intersection))
	{
		return true;
	}
	return false;
}

float MathHeler::AngleBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2)
{
	float dx = cx2 - cx1;
	float dy = cy2 - cy1;

	return atan2(dy, dx) * 180 / M_PI;
}

float MathHeler::AngleBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2)
{
	float cx1 = rect1.x + rect1.w / 2;
	float cy1 = rect1.y + rect1.h / 2;

	float cx2 = rect2.x + rect2.w / 2;
	float cy2 = rect2.y + rect2.h / 2;

	return AngleBetweenTwoPoints(cx1, cy1, cx2, cy2);
}

bool MathHeler::EntityCompare(const Entity* const &a, const Entity* const &b)
{
	if (a != 0 && b != 0)
	{
		return (a->Y < b->Y);
	}
	else
		return false;
}
void MathHeler::RemoveInactiveEntitiesFromList(std::list<Entity*> *entities, bool deleteEntities)
{
	for (auto it = entities->begin(); it != entities->end();)
	{
		if (!(*it)->Active)
		{
			if (deleteEntities)
				delete *it;
			it = entities->erase((it));
		}
		else {
			it++;
		}
	}
}
void MathHeler::RemoveAllFromList(std::list<Entity*> *entities, bool deleteEntities)
{
	for (auto it = entities->begin(); it != entities->end();)
	{
		if (deleteEntities)
			delete *it;
		it = entities->erase((it));
	}
}

