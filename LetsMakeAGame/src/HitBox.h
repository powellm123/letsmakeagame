#pragma once

#include "SDL.h"
#include "IComponent.h"
#include "IScene.h"

class HitBox : public IComponent
{
public:
	static constexpr size_t type = UtilMethods::const_hash("hitbox");
	HitBox(Entity *actor, int collisionBoxWidth, int collisionBoxHeight, int collisionBoxYOffset) : HitBox(actor, collisionBoxWidth, collisionBoxHeight, collisionBoxYOffset, false) {}
	HitBox(Entity *actor, int collisionBoxWidth, int collisionBoxHeight, int collisionBoxYOffset, bool isStaticHitbox);
	virtual void UpdateCollisionBox();
	virtual void UpdateCollisions(); // how we bump into stuff in the world
	void Update() override;
	void Draw() override;

	SDL_Rect CollisionBox; //Box Describing the size of our entity and this is used to bump into things
	SDL_Rect LastCollisionBox; //Where our collision box was last
	int CollisionBoxWidth, CollisionBoxHeight; //our default collisioinBox sizes
	float CollisionBoxYOffset; //From my entities Y value, where should I set this CollisionBox
	bool CollideWithSolids;
	static bool CheckCollision(SDL_Rect &rect1, SDL_Rect &rect2);

	static float DistanceBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2);
	static float AngleBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2);
	static float AngleBetweenTwoRects(SDL_Rect &rect1, SDL_Rect &rect2);
private:
	bool m_isStaticHitBox;
};