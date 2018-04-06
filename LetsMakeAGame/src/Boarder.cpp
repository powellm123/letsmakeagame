
#include "Boarder.h"
#include "SpriteFactory.h"

Boarder::Boarder(float x, float y, int width, int height) : Entity(type, x, y, SpriteFactory::GetSprite("tile", 2)), m_width(width / Globals::TileWidth), m_height(height / Globals::TileHeight)
{
	m_components->emplace_back(new HitBox(this, width, height, true));
}

void Boarder::Draw()
{
	if (m_sprite != nullptr)
		m_sprite->Draw(MathHelper::CreatePoint(X, Y), 0, m_width, m_height);
	for (auto& component : *m_components)
	{
		component->Draw();
	}
}