
#include "HealthBar.h"
#include "Health.h"

HealthBar::HealthBar(Player * actor, float x, float y) : m_actor(actor), posX(x), posY(y)
{
	border = SDL_Sprite::Load("border.png",.5);
	healthbarcolor = SDL_Sprite::Load("healthbar.png",.6);
	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.w = 32;
	clip.h = 32;
	healthbarcolor->SetClip(clip);
}

void HealthBar::Draw()
{
	border->Draw2(Globals::Renderer, posX+40, posY+15, 0, 1, 1);
	if (!m_actor->Active)
	{
		return;
	}
	HealthComponent* h = (HealthComponent*)m_actor->GetComponent("health");

	for (int i = 0; i < h->GetLifePoints(); i++)
	{
		healthbarcolor->Draw2(Globals::Renderer, posX + i * 15, posY + 5, 0, .2, 1);
	}
	
}
