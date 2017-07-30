#include "ComboBox.h"
#include "TextBox.h"
#include "Button.h"

ComboBox::ComboBox(int x, int y, int width, vector<string> _entries) :
Panel(x, y, width), entries(_entries), shouldShowList(false), selectedIndex(0), tempIndex(-1)
{
	text = new TextBox(x + 1, y, width - 3);
	text->setBorder(BorderType::None);
	showList = new Button(x + width - 1, y, 1);
}

size_t ComboBox::GetSelectedIndex()
{
	return selectedIndex;
}

void ComboBox::SetSelectedIndex(size_t index)
{
	selectedIndex = index;
}

void ComboBox::draw(HANDLE h)
{
	DWORD wAttr = getColor(foregroundColor, backgroundColor);

	SetConsoleTextAttribute(h, wAttr);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(h, &info);
	COORD coord = info.dwCursorPosition;

	Panel::draw(h);

	// show according to if shouldShowList is true or not
	if (!shouldShowList)
	{
		COORD c = { x + 1, y };
		SetConsoleCursorPosition(h, c);
		if (entries.size() > 0)
		{
			printf("%s", (*(entries.begin() + selectedIndex)).c_str());
			for (int i = x + (*entries.begin()).size(); i < x + width - 2; i++)
				printf(" ");
		}
	}
	else
	{
		int i = 0;
		for (std::vector<string>::iterator it = entries.begin(); it != entries.end(); ++it)
		{
			COORD c = { x + 1, y + i};
			SetConsoleCursorPosition(h, c);
			printf("%s", (*it).c_str());
			i++;
		}
	}

	SetConsoleCursorPosition(h, coord);
}

bool ComboBox::canFocus()
{
	return true;
}

void ComboBox::setFocus(HANDLE h)
{
	COORD c = { x + 1, y };
	SetConsoleCursorPosition(h, c);
}

bool ComboBox::contains(int _x, int _y)
{
	if (!shouldShowList)
		return Panel::contains(_x, _y);
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

void ComboBox::clickWithMouse(HANDLE h, int _x, int _y)
{
	if (shouldShowList)
	{
		tempIndex = -1;
		selectedIndex = _y - y;
		shouldShowList = false;
		int i = 0;
		for (std::vector<string>::iterator it = entries.begin(); it != entries.end(); ++it)
		{
			COORD c = { x + 1, y + i };
			SetConsoleCursorPosition(h, c);
			for (int j = 0; j < (*it).size(); j++)
				printf(" ");
			i++;
		}
		COORD c = { x + 1, y };
		SetConsoleCursorPosition(h, c);
	}
}

void ComboBox::keyPressed(HANDLE h, KEY_EVENT_RECORD* c)
{
	if (c->uChar.AsciiChar != '\0')
	{
		if (shouldShowList && ((c->uChar.AsciiChar == ' ') || (c->uChar.AsciiChar == '\r')))
		{
			if (tempIndex >= 0)
			{
				shouldShowList = false;
				selectedIndex = tempIndex;
				tempIndex = -1;
				int i = 0;
				for (std::vector<string>::iterator it = entries.begin(); it != entries.end(); ++it)
				{
					COORD c = { x + 1, y + i };
					SetConsoleCursorPosition(h, c);
					for (int j = 0; j < (*it).size(); j++)
						printf(" ");
					i++;
				}
				COORD c = { x + 1, y };
				SetConsoleCursorPosition(h, c);
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
				shouldShowList = true;
			}
			break;
		}
	}
}


