
#include "PlayerSelectEntity.h"

#include <sstream>
#include "ControllerGather.h"
#include "IScene.h"
#include "TimeController.h"
#include "Helper_Functions.h"
#include "LevelCreator.h"

PlayerSelectEntity::PlayerSelectEntity(ControllerGather* cg, Buttons *buttons, int playerNumber) : Player(type, buttons)
{
	m_cg = cg;
	m_sprite = SpriteFactory::GetSprite("tank", 0);
	Y = Globals::ScreenHeight / 2;
	int posX = (Globals::ScreenWidth - 200) / 4;
	X = 100 + posX * playerNumber;
	boarder = new PlayerSelectBoarder(X, 0);
	IScene::m_spriteobjects->push_back(boarder);
	m_selected = false;
	m_justChanged = .1;

	//LevelCreator::Instance.AddPlayer(this);

	//generate score text
	SDL_Color color = { 255, 255, 255, 255 };
	std::stringstream ss;
	ss << "Ready";

	readyText = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 30, Globals::Renderer);
}

PlayerSelectEntity::PlayerSelectEntity(ControllerGather* cg, SDL_JoystickID joystickId, int playerNumber) : Player(type, joystickId)
{
	m_buttons = *Globals::KeyboardButtons;
	m_cg = cg;
	m_sprite = SpriteFactory::GetSprite("tank", 0);
	Y = Globals::ScreenHeight / 2;
	int posX = (Globals::ScreenWidth - 200) / 4;
	X = 100 + posX * playerNumber;
	boarder = new PlayerSelectBoarder(X, 0);
	IScene::m_spriteobjects->push_back(boarder);
	m_joystickId = joystickId;
	m_selected = false;
	m_justChanged = .1;

	//LevelCreator::Instance.AddPlayer(this);

	//generate score text
	SDL_Color color = { 255, 255, 255, 255 };
	std::stringstream ss;
	ss << "Ready";

	readyText = renderText(ss.str(), Globals::GetResourcePath() + "Bombardment.ttf", color, 30, Globals::Renderer);
}

PlayerSelectEntity::~PlayerSelectEntity()
{
	//LevelCreator::Instance.RemovePlayer(this);
	boarder->SetActive(false);
	if(m_cg != nullptr)
		(m_cg)->RemoveInput(m_joystickId);
}

bool PlayerSelectEntity::IsSelected()
{
	return m_selected;
}

void PlayerSelectEntity::ResetReady()
{
	m_ready = false;
}

bool PlayerSelectEntity::Ready()
{
	return m_ready;
}

void PlayerSelectEntity::PerformAction(Player::Action action) 
{
	if (m_justChanged > 0)
	{
		return;
	}
	switch (action)
	{
	case Player::Action::Fire:
	case Player::Action::Pause:
		m_selected = true;
		if (m_isReady)
			m_ready = true;
		break;
	case Player::Action::AltFire:
		if (m_selected)
			m_selected = false;
		else {
			Alive = false;

			//IScene::m_entities->remove(this);
			//delete this;
		}
		break;
	}
	m_justChanged = .1;
}

void PlayerSelectEntity::PerformMove(float angle, float value) 
{
	if (m_justChanged > 0)
	{
		return;
	}
	if (angle > -90 && angle < 90)
		m_currentSprite = min(m_currentSprite + 1, 3);
	else
		m_currentSprite = max(m_currentSprite - 1, 0);

	m_sprite = SpriteFactory::GetSprite("tank", m_currentSprite);
	m_justChanged = .1;
}

void PlayerSelectEntity::Update(bool isReady)
{
	m_isReady = isReady;
	Player::Update();
	if (m_justChanged > 0)
		m_justChanged -= TimeController::instance.DeltaTime;
}

void PlayerSelectEntity::Draw(bool drawReady)
{
	Entity::Draw();
	if(m_selected && drawReady)
		renderTexture(readyText, Globals::Renderer, X, Y);
}
