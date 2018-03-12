#pragma once

#include "Entity.h"
#include "HitBox.h"
#include "TimeController.h"

class Explosion : public Entity
{
public:
	Explosion(float x, float y) : Entity("explosion", x, y, SDL_Sprite::Load(0, 0, 32, 32, "explosion.png"))
	{
		LifeSpan = 1;
		m_components->emplace_back(new HitBox(this, 32, 32, -16));
	}
	void Update() override
	{
		if (!Active)
			return;

		Entity::Update();

		LifeSpan -= TimeController::instance.DeltaTime;

		if (LifeSpan <= 0)
			Active = false;
	}
	void Draw() override
	{
		m_sprite->Draw(Globals::Renderer, X, Y, 0);
		for (auto& component : *m_components)
		{
			component->Draw();
		}
	}
private:
	float LifeSpan;
};