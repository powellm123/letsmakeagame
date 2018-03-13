
#include "PowerUp.h"

PowerUp::PowerUp(float x, float y, PowerUp::PowerUpType type, SDL_Sprite* sprite) : Entity("powerup", x, y, sprite)
{
	m_components->emplace_back(new HitBox(this, 32, 32, -16, true));
	m_powerupType = type;
}

void PowerUp::CreatePowerUp(float x, float y)
{
	switch (rand() % 3) {
	case 0:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::SpeedUp, SDL_Sprite::Load(0, 0, 32, 32, "powerup.png")));
		break;
	case 1:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::ShotUp, SDL_Sprite::Load(0, 0, 32, 32, "shotup.png")));
		break;
	case 2:
		IScene::m_entities->emplace_back(new PowerUp(x, y, PowerUp::PowerUpType::ShotCountUp, SDL_Sprite::Load(0, 0, 32, 32, "shotcountup.png")));
		break;
	}
}