#include "KeyboardInput.h"
#include "Entity.h"
#include "Movable.h"

void KeyboardInput::Update()
{
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	auto movableComponent = (Movable*) m_actor->GetComponent(Movable::type);
	//if movableComponent not able to move or no direction buttons are being held down, then stop moving (slide to a halt)
	if ((movableComponent->GetMoveState() != Movable::MoveState::MOVE && movableComponent->GetMoveState() != Movable::MoveState::IDEL)
		|| (!keys[UP] && !keys[DOWN] && !keys[LEFT] && !keys[RIGHT]))
	{
		movableComponent->SetIsMoving(false);
	}
	else {
		//ups
		if (keys[UP])
		{
			//upright
			//if (keys[RIGHT])
			//{
			//	movableComponent->Move(270 + 45);
			//}
			//else if (keys[LEFT])
			//{
			//	movableComponent->Move(270 - 45);
			//}
			//else {
				movableComponent->Move(); //270
			//}
		}
		else if (keys[DOWN])
		{
			//downright
			//if (keys[RIGHT])
			//{
			//	movableComponent->Move(90 - 45);
			//}
			//else if (keys[LEFT])
			//{
			//	movableComponent->Move(90 + 45);
			//}
			//else {
				movableComponent->Move(); //90
			//}
		}
		else if (keys[LEFT])
		{
			movableComponent->Rotate(-5);
			//movableComponent->Move(180);
		}
		else if (keys[RIGHT])
		{
			movableComponent->Rotate(5);
			//movableComponent->Move(0);
		}
	}

}

void KeyboardInput::Draw()
{
}
