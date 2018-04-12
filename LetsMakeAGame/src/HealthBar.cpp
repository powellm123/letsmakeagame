
#include "HealthBar.h"
#include "Health.h"
#include "SpriteFactory.h"

HealthBar::HealthBar(Player * actor, float x, float y) : m_actor(actor), posX(x), posY(y)
{
	for(int i = 0; i < 9; i++)
		border[i] = SpriteFactory::GetSprite("border", i);
	healthbarcolor = SpriteFactory::GetSprite("healthbar", 0);
}

HealthBar::~HealthBar()
{
	delete healthbarcolor;
	delete border;
}

void HealthBar::Draw()
{
	static const int widthSize = 5;
	static const int heightSize = 2;

	for (int i = 0, k = 0; i < heightSize; i++)
	{
		for (int j = 0; j < widthSize; j++)
		{
			if (k == 0 || k == 2 || k == 3 || k == 5 || k == 6 || k == 8) {
				border[k]->Draw(MathHelper::CreatePoint(posX + ((j) * 16), posY + ((i ) * 16)), 0, .5, .5);
				k++;
			}
			else
			{
				border[k]->Draw(MathHelper::CreatePoint(posX + ((j) * 16), posY + ((i ) * 16)), 0, .5, .5);
				if (j == widthSize - 2 )
					k++;
			}
		}
		if (i == heightSize - 2)
			k = 6;		
		else
			k = 3;
	}

	if (!m_actor->Active)
	{
		return;
	}
	HealthComponent* h = (HealthComponent*)m_actor->GetComponent(HealthComponent::type);

	for (int i = 0; i < h->GetLifePoints(); i++)
	{
		healthbarcolor->Draw(MathHelper::CreatePoint(posX + i * 10 + 35, posY + 5), 0, .3, .6);
	}
}
