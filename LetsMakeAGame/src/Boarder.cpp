
#include "Boarder.h"

Boarder::Boarder(float x, float y, int width, int height, Sprite* sprite) : Entity(type, x, y, sprite), m_width(width / 32), m_height(height / 32)
{
	m_components->emplace_back(new HitBox(this, width, height, -16, true));
}

void Boarder::Draw()
{
	if (m_sprite != nullptr)
		m_sprite->Draw(MathHelper::CreatePoint(X, Y), 0, MathHelper::CreatePoint( m_width, m_height));
	for (auto& component : *m_components)
	{
		component->Draw();
	}
}