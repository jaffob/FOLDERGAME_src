// FG_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

bool stringIsAlphanumeric(std::string s)
{
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (!isalnum(s[i]))
			return false;
	}
	return true;
}

int main()
{
	string input;
	while (true)
	{
		// Take input name and ensure validity.
		cout << "Enter the name of the input set (or \"exit\"): ";
		cin >> input;

		if (!input.compare("exit"))
			return 0;

		if (!stringIsAlphanumeric(input))
			continue;

		// Open the map and solution bitmaps.
		bitmap_image map(input + "_map.bmp");
		bitmap_image soln(input + "_solution.bmp");

		// Both must exist.
		if (!map || !soln)
			continue;

		// Ensure map is correct size.
		if (map.width() != 256 || map.height() != 256)
			continue;

		Minigame1 mg1(map, soln);

		if (mg1.play())
			cout << "SUCCESS" << endl;
		else
			cout << "FAIL" << endl;
	}
}

