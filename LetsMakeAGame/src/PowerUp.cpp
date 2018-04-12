
#include "PowerUp.h"
#include "SpriteFactory.h"
#include "SoundManager.h"

PowerUp::PowerUp(float x, float y, PowerUp::PowerUpType ptype, Sprite* sprite) : Entity(type, x, y, sprite)
{
	m_components->emplace_back(new HitBox(this, 32, 32, true));
	m_powerupType = ptype;

}

void PowerUp::Update()
{
	if (GetIsDying())
	{
		SoundManager::Instance.PlayASound(1002);
	}

	Entity::Update();
}

void PowerUp::CreatePowerUp(float x, float y)
{
	switch (rand() % 7) {
	case 0:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::ShotUp, SpriteFactory::GetSprite("powerup", 0)));
		break;
	case 1:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::SpeedUp, SpriteFactory::GetSprite("powerup", 1)));
		break;
	case 2:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::ShotCountUp, SpriteFactory::GetSprite("powerup", 2)));
		break;
	case 3:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::ExplosionUp, SpriteFactory::GetSprite("powerup", 3)));
		break;
	case 4:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::CannonBall, SpriteFactory::GetSprite("powerup", 4)));
		break;
	case 5:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::FlameThrower, SpriteFactory::GetSprite("powerup", 5)));
		break;
	case 6:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::Mine, SpriteFactory::GetSprite("powerup", 6)));
		break;
	}
}