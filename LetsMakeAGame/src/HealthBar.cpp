
#include "HealthBar.h"
#include "Health.h"
#include "SpriteManager.h"

HealthBar::HealthBar(Player * actor, float x, float y) : m_actor(actor), posX(x), posY(y)
{
	border = SpriteManager::LoadTileSet("boarder.png", 183, 64)->GetSprite(0); // SDL_Sprite::Load("border.png",.5);
	healthbarcolor = SpriteManager::LoadTileSet("healthbar.png", 32, 32)->GetSprite(0); // SDL_Sprite::Load("healthbar.png", .6);
}

HealthBar::~HealthBar()
{
	delete healthbarcolor;
	delete border;
}

void HealthBar::Draw()
{
	border->Draw(MathHelper::CreatePoint(posX+50, posY+15), 0, MathHelper::CreatePoint( .5, .5));
	if (!m_actor->Active)
	{
		return;
	}
	HealthComponent* h = (HealthComponent*)m_actor->GetComponent(HealthComponent::type);

	for (int i = 0; i < h->GetLifePoints(); i++)
	{
		healthbarcolor->Draw(MathHelper::CreatePoint(posX + i * 15, posY + 5), 0, MathHelper::CreatePoint(.1, .6));
	}
	
}
