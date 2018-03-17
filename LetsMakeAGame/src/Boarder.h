#pragma once

#include "Entity.h"
#include "HitBox.h"
#include "Sprite.h"

class Boarder : public Entity
{
	int m_width;
	int m_height;
public:
	static constexpr size_t type = UtilMethods::const_hash("boarder");
	Boarder(float x, float y, int width, int height);
	void Draw() override;
};