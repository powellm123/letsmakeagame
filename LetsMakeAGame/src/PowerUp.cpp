
#include "PowerUp.h"
#include "SpriteManager.h"


PowerUp::PowerUp(float x, float y, PowerUp::PowerUpType ptype, Sprite* sprite) : Entity(type, x, y, sprite)
{
	m_components->emplace_back(new HitBox(this, 32, 32, -16, true));
	m_powerupType = ptype;

}

void PowerUp::CreatePowerUp(float x, float y)
{
	static SpriteSheet *powerUps = SpriteManager::LoadTileSet("PowerUpTileSet.png", 128, 128);
	switch (rand() % 4) {
	case 0:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::SpeedUp, powerUps->GetSprite(0)));
		break;
	case 1:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::ShotUp, powerUps->GetSprite(1)));
		break;
	case 2:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::ShotCountUp, powerUps->GetSprite(2)));
		break;
	case 3:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::ExplosionUp, powerUps->GetSprite(3)));
		break;
	}
}