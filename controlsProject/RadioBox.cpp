#include "RadioBox.h"

RadioBox::RadioBox(int x, int y, int width, vector<string> entries) :
	CheckList(x, y, width, entries)
{

}

void RadioBox::keyPressed(HANDLE h, KEY_EVENT_RECORD* c)
{
	if (c->uChar.AsciiChar != '\0')
	{
		if ((c->uChar.AsciiChar == ' ') || (c->uChar.AsciiChar == '\r'))
		{
			if (tempIndex >= 0)
			{
				selectedIndices.clear();
				selectedIndices.push_back(tempIndex);
			}
		}
		else
			CheckList::keyPressed(h, c);
	}
	else
	{
		CheckList::keyPressed(h, c);
	}
}

void RadioBox::clickWithMouse(HANDLE h, int _x, int _y)
{
	int index = _y - y;
	tempIndex = index;
	selectedIndices.clear();
	selectedIndices.push_back(tempIndex);
}

