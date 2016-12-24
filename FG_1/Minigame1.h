#pragma once
#include "stdafx.h"

class Minigame1
{
private:
	bitmap_image map, soln;
	int x, y, dx, dy;
	int token, nl, ntoken;
	int solnx, solny;

private:

	inline bool isInBounds(int x, int y)
	{
		return x >= 0 && y >= 0 && x < 256 && y < 256;
	}

	inline bool isPlayable(rgb_t &pixel)
	{
		return pixel.red > 0 || pixel.green > 0 || pixel.blue > 0;
	}

public:
	Minigame1(bitmap_image &map, bitmap_image &soln);
	bool play();
};