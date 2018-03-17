
#include "Explosion.h"
#include "SpriteManager.h"
#include "SpriteFactory.h"


Explosion::Explosion(float x, float y, int size) : Entity(type, x - size/2, y+size/2, SpriteFactory::GetSprite("bullet", 2)), m_size(1+(size/3.0))
{
	LifeSpan = 1;
	m_components->emplace_back(new HitBox(this, Globals::TileWidth * m_size, Globals::TileHeight * m_size, -16));
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
	m_sprite->Draw(MathHelper::CreatePoint(X, Y), m_size, m_size);
	for (auto& component : *m_components)
	{
		component->Draw();
	}
}