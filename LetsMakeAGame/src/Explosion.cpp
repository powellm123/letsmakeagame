
#include "Explosion.h"
#include "SpriteManager.h"

SpriteSheet* Explosion::explosions = SpriteManager::LoadTileSet("explosion.png", 32, 32);

Explosion::Explosion(float x, float y, int size) : Entity(type, x, y, explosions->GetSprite(0)), m_size(1+(size/3.0))
{
	LifeSpan = 1;
	m_components->emplace_back(new HitBox(this, 32 * m_size, 32 * m_size, -16));
}
void Explosion::Update()
{
	if (!Active)
		return;

	Entity::Update();

	LifeSpan -= TimeController::instance.DeltaTime;

	if (LifeSpan <= 0)
		Active = false;
}
void Explosion::Draw() 
{
	//m_sprite->Draw2(Globals::Renderer, X, Y, 0, m_size, m_size);
	m_sprite->Draw(MathHelper::CreatePoint(X, Y), MathHelper::CreatePoint(m_size, m_size));
	for (auto& component : *m_components)
	{
		component->Draw();
	}
}