
#include "Explosion.h"
#include "SpriteFactory.h"
#include "SoundManager.h"

Explosion::Explosion(float x, float y, int size) : Entity(type, x , y, SpriteFactory::GetSprite("bullet", 2)), m_size(1+(size/3.0))
{
	LifeSpan = 1;
	float scaledx = m_sprite->GetSpritCord().w * m_sprite->GetScale() * (m_size/2);
	float scaledy = m_sprite->GetSpritCord().h * m_sprite->GetScale() * (m_size/2);
	
	X -= scaledx / 2;
	Y -= scaledy / 2;

	m_components->emplace_back(new HitBox(this, (Globals::TileWidth -12)* m_size, (Globals::TileHeight -12) * m_size, false, -5- (scaledx-16)/4.0, -8 - (scaledy-16)/4.0));
	SoundManager::Instance.PlayASound(ExplosionSound);
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
	m_sprite->Draw(MathHelper::CreatePoint(X, Y), m_size, m_size);
	for (auto& component : *m_components)
	{
		component->Draw();
	}
}
