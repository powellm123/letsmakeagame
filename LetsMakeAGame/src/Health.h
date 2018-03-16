#pragma once
#include <SDL.h>
#include "IComponent.h"
#include "TimeController.h"

class HealthComponent : public IComponent
{
public:
	static constexpr size_t type = UtilMethods::const_hash("health");
	const enum class HealthStatus {Alive, Dead};
	HealthComponent(Entity * actor, int health);
	void Damage(int amount);

	void Update() override;
	void Draw() override;
	int GetLifePoints();
private:
	HealthStatus m_status;
	int Health, MaxHealth;
	float invincibleTimer;
	SDL_Rect Hitbox;
};