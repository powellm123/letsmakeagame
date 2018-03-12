#pragma once
#include "SDL.h"
#include "MathHelper.h"

const enum GridType { unsolved, open, dirtwall, wall, tank, powerup };

class MapSpot
{
public:
	bool Checked;
	GridType GridType;
	int HCost;
	int GCost;
	int FCost;
	SDL_Point Direction;
	SDL_Point Loc;
	void CalcFCost() { FCost = HCost + GCost; }
	void ResetHiristic(int x, int y) {
		FCost = INT32_MAX;
		HCost = 0;
		GCost = 0;
		Direction = MathHelper::CreatePoint(0, 0);
		Loc = MathHelper::CreatePoint(x, y);
		Checked = false;
	}
	MapSpot()
	{
		GridType = GridType::open;
		FCost = INT32_MAX;
		HCost = 0;
		GCost = 0;
		Direction = MathHelper::CreatePoint(0, 0);
		Loc = MathHelper::CreatePoint(0, 0);
		Checked = false;
	}
};