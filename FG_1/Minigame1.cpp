#include "stdafx.h"

Minigame1::Minigame1(bitmap_image & map, bitmap_image & solution)
{
	this->map = map;
	this->soln = solution;
}

bool Minigame1::play()
{
	// Get start position.
	rgb_t mc, sc;
	map.get_pixel(0, 0, mc);

	// Initialize stuff.
	x = mc.red, y = mc.green, dx = 1, dy = 0;
	token = nl = 255;
	ntoken = mc.blue;
	solnx = solny = 0;

	while (true)
	{ 
		// Make sure the current location is in bounds and walkable.
		if (!isInBounds(x, y)) return false;
		map.get_pixel(x, y, mc);
		if (!isPlayable(mc)) return false;

		// Read current solution pixel.
		soln.get_pixel(solnx, solny, sc);

		// Turn right command.
		if (sc.red == 255 && sc.green == 255 && sc.blue == 255)
		{
			int dy_old = dy;
			dy = dx;
			dx = -dy_old;
		}

		// Walk forward command.
		else if (sc.red == 0 && sc.green > 0 && sc.blue == 0)
		{
			int dist = sc.green;

			// Ensure destination is in bounds.
			if (!isInBounds(x + dx * dist, y + dy * dist)) return false;

			for (int i = 0; i < dist; i++)
			{
				x += dx;
				y += dy;
				map.get_pixel(x, y, mc);
				if (!isPlayable(mc)) return false;
			}
		}

		// Collect token command.
		else if (sc.red > 0 && sc.green == 0 && sc.blue == 0)
		{
			if (sc.red == mc.red && sc.red == token && mc.green == 0 && mc.blue == 0) {
				token--;
			}
			else {
				return false;
			}
		}

		// Teleporter command.
		else if (sc.red == 0 && sc.green == 0 && sc.blue > 0)
		{
			// Fail if not standing on the right teleporter.
			if (mc != sc) return false;

			// Find the other teleporter.
			int telex = -1, teley = -1;
			rgb_t telec;
			for (int i = 0; i < (signed)map.width(); i++)
			{
				for (int j = 0; j < (signed)map.height(); j++)
				{
					map.get_pixel(i, j, telec);
					if (telec == mc && (i != x || j != y))
					{
						if (isInBounds(telex, teley)) return false;
						telex = i;
						teley = j;
					}
				}
			}

			if (!isInBounds(telex, teley)) return false;
			x = telex;
			y = teley;
		}

		// Finish game command.
		else if (sc.red == 0 && sc.green == 0 && sc.blue == 0)
		{
			// Get bottom right pixel to determine end pos and num new lines.
			map.get_pixel(255, 255, mc);

			if (x == mc.red && y == mc.green && token == 255 - ntoken && nl == 255 - mc.blue) {
				return true;
			}
			else {
				return false;
			}
		}

		// Those were the only options.
		else
		{
			return false;
		}

		// Advance the solution pixel, ensuring newlines are observed.
		solnx++;
		if (solnx >= (signed)soln.width())
		{
			// Advance soln pixel to next line, making sure there is a next line.
			solny++;
			solnx = 0;
			if (solny >= (signed)soln.height()) return false;

			// Make sure we're standing on a correct newline map pixel.
			map.get_pixel(x, y, mc);
			if (mc.red == 0 && mc.blue == 0 && mc.green == nl)
			{
				nl--;
			} else {
				return false;
			}
		}
	}
}
