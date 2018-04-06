#pragma once

#include "SpriteObjects.h"
#include "SpriteFactory.h"
#include "SpriteSheet.h"

class PlayerSelectBoarder : public SpriteObjects
{
private:
	Sprite* border[9];
	float X, Y;
public:
	PlayerSelectBoarder(float x, float y);
	void Draw() override;
};