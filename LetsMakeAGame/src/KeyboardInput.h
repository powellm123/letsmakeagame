#pragma once
#include "SDL.h"
#include "IComponent.h"

class KeyboardInput : public IComponent
{
public:
	SDL_Scancode UP, DOWN, LEFT, RIGHT;
	KeyboardInput(Entity *actor) : IComponent(actor, "KeyboardInput") {
		//Hard coded keyboard buttons
		UP = SDL_SCANCODE_UP;
		DOWN = SDL_SCANCODE_DOWN;
		RIGHT = SDL_SCANCODE_RIGHT;
		LEFT = SDL_SCANCODE_LEFT;
	}
	void Update() override;
	void Draw() override;
};