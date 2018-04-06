#include "PlayerSelectBoarder.h"
#include "MathHelper.h"

PlayerSelectBoarder::PlayerSelectBoarder(float x, float y) : X(x), Y(y)
{
	for (int i = 0; i < 9; i++)
		border[i] = SpriteFactory::GetSprite("border", i);
}

void PlayerSelectBoarder::Draw()
{
	static const int widthSize = 7;
	static const int heightSize = Globals::ScreenHeight/Globals::TileHeight *2;

	for (int i = 0, k = 0; i < heightSize; i++)
	{
		for (int j = 0; j < widthSize; j++)
		{
			if (k == 0 || k == 2 || k == 3 || k == 5 || k == 6 || k == 8) {
				border[k]->Draw(MathHelper::CreatePoint(X + ((j) * 16), Y + ((i) * 16)), 0, .5, .5);
				k++;
			}
			else
			{
				border[k]->Draw(MathHelper::CreatePoint(X + ((j) * 16), Y + ((i) * 16)), 0, .5, .5);
				if (j == widthSize - 2)
					k++;
			}
		}
		if (i == heightSize - 2)
			k = 6;
		else
			k = 3;
	}
}
