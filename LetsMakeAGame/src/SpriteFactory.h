#pragma once

#include "SpriteSheet.h"
#include <map>
#include <string>

class SpriteFactory
{
	static std::map< unsigned, SpriteSheet*> _cache;
public:
	static void AddSpriteSheet(std::string filename, std::string name, int width = 128, int height = 128);
	static Sprite* GetSprite(std::string name, int index);
};