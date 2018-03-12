
#include "Entity.h"
#include "MathHelper.h"

//Helper
float MathHelper::DistanceBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2)
{
	SDL_Point e1, e2;
	e1.x = rect1.x + rect1.w / 2;
	e1.y = rect1.y + rect1.h / 2;

	e2.x = rect2.x + rect2.w / 2;
	e2.y = rect2.y + rect2.h / 2;

	float d = abs(sqrt(pow(e2.x - e1.x, 2) + pow(e2.y - e1.y, 2)));
	return d;
}
float MathHelper::DistanceBetweenTwoEntities(Entity *e1, Entity *e2)
{
	return abs(sqrt(pow(e2->X - e1->X, 2) + pow(e2->Y - e1->Y, 2)));
}


float MathHelper::DistanceBetweenTwoEntitiesBy32(Entity *e1, Entity* e2)
{
	return (pow(e2->X - e1->X, 2) + pow(e2->Y - e1->Y, 2))/1024.0;
}

float MathHelper::DistanceBetweenPointAndEntity(SDL_Point *p, Entity* e)
{
	return (pow(e->X - p->x, 2) + pow(e->Y - p->y, 2)) / 1024.0;
}


float MathHelper::DistanceBetweenTwoPoints(SDL_Point *p, SDL_Point* e)
{
	return (pow(e->x - p->x, 2) + pow(e->y - p->y, 2));
}

float MathHelper::AngleBetweenTwoEntities(Entity *e1, Entity *e2)
{
	float dx, dy;
	float x1 = e1->X, y1 = e1->Y, x2 = e2->X, y2 = e2->Y;

	dx = x2 - x1;
	dy = y2 - y1;

	return atan2(dy, dx) * 180 / M_PI;
}


float MathHelper::AngleBetweenPointAndEntities(SDL_Point *p, Entity *e)
{
	float dx, dy;
	float x1 = p->x, y1 = p->y, x2 = e->X, y2 = e->Y;

	dx = x2 - x1;
	dy = y2 - y1;

	return atan2(dy, dx) * 180 / M_PI;
}

bool MathHelper::CheckCollision(SDL_Rect &rect1, SDL_Rect &rect2)
{
	SDL_Rect intersection;
	if (SDL_IntersectRect(&rect1, &rect2, &intersection))
	{
		return true;
	}
	return false;
}

float MathHelper::AngleBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2)
{
	float dx = cx2 - cx1;
	float dy = cy2 - cy1;

	return atan2(dy, dx) * 180 / M_PI;
}

float MathHelper::AngleBetweenTwoPointsR(SDL_Point c1, SDL_Point c2)
{
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;

	return atan2(dy, dx);
}

float MathHelper::AngleBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2)
{
	float cx1 = rect1.x + rect1.w / 2.0;
	float cy1 = rect1.y + rect1.h / 2.0;

	float cx2 = rect2.x + rect2.w / 2.0;
	float cy2 = rect2.y + rect2.h / 2.0;

	return AngleBetweenTwoPoints(cx1, cy1, cx2, cy2);
}

SDL_Point MathHelper::CreatePoint(int x, int y)
{
	SDL_Point p;
	p.x = x;
	p.y = y;
	return p;
}

SDL_Point MathHelper::ReducePoint(SDL_Point p)
{
	SDL_Point rp = p;
	rp.x /= 32;
	rp.y /= 32;

	return rp;
}

bool MathHelper::EntityCompare(const Entity* const &a, const Entity* const &b)
{
	if (a != 0 && b != 0)
	{
		return (a->Y < b->Y);
	}
	else
		return false;
}
void MathHelper::RemoveInactiveEntitiesFromList(std::list<Entity*> *entities, bool deleteEntities)
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
void MathHelper::RemoveAllFromList(std::list<Entity*> *entities, bool deleteEntities)
{
	for (auto it = entities->begin(); it != entities->end();)
	{
		if (deleteEntities)
			delete *it;
		it = entities->erase((it));
	}
}

