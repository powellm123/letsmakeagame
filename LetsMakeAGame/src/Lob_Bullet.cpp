
#include "Lob_Bullet.h"

Lob_Bullet::Lob_Bullet(float x, float y, float angle) : Bullet(SDL_Sprite::Load(0, 0, 32, 32, "altbullet1.png"), x, y, angle, 1000)
{
	Z = 0;
	Z_volicity = 2;
	Z_acc = -9.8;

	m_components->pop_back();
}

void Lob_Bullet::Update()
{
	if (!Active)
		return;
	float dt = TimeController::instance.DeltaTime;
	Z = Z + Z_volicity * dt + Z_acc * dt * dt;
	Z_volicity = Z_volicity + Z_acc * dt;

	Bullet::Update();

	if (Z <= 0)
	{
		SetIsDying(true);
	}
}
