#include "CheckList.h"
#include <algorithm>

CheckList::CheckList(int x, int y, int width, vector<string> _entries) :
Panel(x, y, width), entries(_entries), tempIndex(-1)
{
}

vector<size_t> CheckList::GetSelectedIndices()
{
	return selectedIndices;
}

void CheckList::SelectIndex(size_t index)
{
	if (std::find(selectedIndices.begin(), selectedIndices.end(), index) == selectedIndices.end())
		selectedIndices.push_back(index);
}

void CheckList::DeselectIndex(size_t index)
{
	std::vector<size_t>::iterator iter = std::find(selectedIndices.begin(), selectedIndices.end(), index);
	selectedIndices.erase(iter);
}

void CheckList::draw(HANDLE h)
{
	DWORD wAttr = getColor(foregroundColor, backgroundColor);

	SetConsoleTextAttribute(h, wAttr);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(h, &info);
	COORD coord = info.dwCursorPosition;

	COORD c = { SHORT(x), SHORT(y - 1) };

	SetConsoleCursorPosition(h, c);
	printf("%c", '\xDA');
	for (short i = 0; i < width - 1; i++) {
		printf("%c", '\xC4');
	}
	printf("%c", '\xBF');

	int i = 0;
	for (std::vector<string>::iterator it = entries.begin(); it != entries.end(); ++it)
	{
		COORD c = { x, y + i };
		SetConsoleCursorPosition(h, c);
		if (std::find(selectedIndices.begin(), selectedIndices.end(), i) != selectedIndices.end())
		{
			printf("%c * ", '\xB3');
		}
		else
		{
			printf("%c   ", '\xB3');
		}
		printf("%s", (*it).c_str());
		c = { SHORT(x + width), SHORT(y + i) };
		SetConsoleCursorPosition(h, c);
		printf("%c", '\xB3');
		i++;
	}

	c = { SHORT(x), SHORT(y + entries.size()) };
	SetConsoleCursorPosition(h, c);
	printf("%c", '\xc0');
	for (short i = 0; i < width - 1; i++) {
		printf("%c", '\xC4');
	}
	printf("%c", '\xd9');
	SetConsoleCursorPosition(h, coord);
}

bool CheckList::AddSelectedItem(string item)
{
	int i = 0;
	for (std::vector<string>::iterator it = entries.begin(); it != entries.end(); ++it)
	{
		if ((*it) == item)
		{
			std::vector<size_t>::iterator iter = std::find(selectedIndices.begin(), selectedIndices.end(), tempIndex);
			if (iter == selectedIndices.end())
				selectedIndices.push_back(i);
			return true;
		}
		i++;
	}
	return false;
}

bool CheckList::RemoveSelectedItem(string item)
{
	int i = 0;
	for (std::vector<string>::iterator it = entries.begin(); it != entries.end(); ++it)
	{
		if ((*it) == item)
		{
			std::vector<size_t>::iterator iter = std::find(selectedIndices.begin(), selectedIndices.end(), tempIndex);
			if (iter != selectedIndices.end())
				selectedIndices.erase(iter);
			return true;
		}
		i++;
	}
	return false;
}

bool CheckList::canFocus()
{
	return true;
}

void CheckList::setFocus(HANDLE h)
{
	COORD c = { x + 1, y };
	SetConsoleCursorPosition(h, c);
}

void CheckList::keyPressed(HANDLE h, KEY_EVENT_RECORD* c)
{
	if (c->uChar.AsciiChar != '\0')
	{
		if ((c->uChar.AsciiChar == ' ') || (c->uChar.AsciiChar == '\r'))
		{
			if (tempIndex >= 0)
			{
				std::vector<size_t>::iterator iter = std::find(selectedIndices.begin(), selectedIndices.end(), tempIndex);
				if (iter == selectedIndices.end())
					selectedIndices.push_back(tempIndex);
				else
					selectedIndices.erase(iter);
			}
		}
		else
			if (c->uChar.AsciiChar == '\t')
			{
				if (tempIndex < 0)
					tempIndex = 0;
				if (tempIndex < int(entries.size()))
				{
					CONSOLE_SCREEN_BUFFER_INFO info;
					GetConsoleScreenBufferInfo(h, &info);
					COORD coord = info.dwCursorPosition;
					tempIndex++;
					coord.Y++;
					SetConsoleCursorPosition(h, coord);
				}
			}
	}
	else
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(h, &info);
		COORD coord = info.dwCursorPosition;
		switch (c->wVirtualKeyCode)
		{
		case UP_KEY:
			if (tempIndex > 0)
			{
				tempIndex--;
				coord.Y--;
				SetConsoleCursorPosition(h, coord);
			}
			break;
		case DOWN_KEY:
			if (tempIndex < 0)
				tempIndex = 0;
			if (tempIndex < int(entries.size()))
			{
				tempIndex++;
				coord.Y++;
				SetConsoleCursorPosition(h, coord);
			}
			break;
		}
	}
}

bool CheckList::shouldChangeFocusOnTab(HANDLE h)
{
	if (tempIndex == entries.size() - 1)
	{
		tempIndex = -1;
		COORD c = { x + 1, y };
		SetConsoleCursorPosition(h, c);
		int i = 0;
		for (std::vector<string>::iterator it = entries.begin(); it != entries.end(); ++it)
		{
			c = { x + 1, y + i };
			SetConsoleCursorPosition(h, c);
			for (int j = 0; j < (*it).size() + 2; j++)
				printf(" ");
			i++;
		}
		return true;
	}
	return false;
}

bool CheckList::contains(int _x, int _y)
{
	if (Panel::contains(_x, _y))
		return true;
	int i = 0;
	for (std::vector<string>::iterator it = entries.begin(); it != entries.end(); ++it)
	{
		if ((_y == y + i) && (_x >= x + 1) && (_x < x + (*it).size()))
			return true;
		i++;
	}
	return false;
}

void CheckList::clickWithMouse(HANDLE h, int _x, int _y)
{
	int index = _y - y;
	tempIndex = index;
	std::vector<size_t>::iterator iter = std::find(selectedIndices.begin(), selectedIndices.end(), tempIndex);
	if (iter == selectedIndices.end())
		selectedIndices.push_back(tempIndex);
	else
		selectedIndices.erase(iter);
}


