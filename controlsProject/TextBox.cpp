#include "TextBox.h"
#include <algorithm>

TextBox::TextBox(int x, int y, int width) : Control(x, y, width)
{

}
std::string TextBox::GetText()
{
	return text;
}
void TextBox::SetText(std::string newText)
{
	text = newText;
}

void TextBox::draw(HANDLE h)
{
	DWORD wAttr = getColor(foregroundColor, backgroundColor);

	SetConsoleTextAttribute(h, wAttr);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(h, &info);
	COORD coord = info.dwCursorPosition;
	Control::draw(h);
	COORD c = { SHORT(x + 1), SHORT(y) };
	SetConsoleCursorPosition(h, c);
	printf("%s", GetText().c_str());
	for (int i = x + text.size(); i < x + width - 1; i++)
	{
		printf(" ");
	}
	SetConsoleCursorPosition(h, coord);
}

void TextBox::setFocus(HANDLE h)
{
	COORD c = { x + 1, y };
	SetConsoleCursorPosition(h, c);
}

void TextBox::keyPressed(HANDLE h, KEY_EVENT_RECORD* c)
{
	if (c->uChar.AsciiChar != '\0')
	{
		if (c->uChar.AsciiChar == '\b') // back space
		{
			CONSOLE_SCREEN_BUFFER_INFO info;
			GetConsoleScreenBufferInfo(h, &info);
			COORD coord = info.dwCursorPosition;
			int index = coord.X - x - 1;
			if ((index > 0) && (index <= text.size()))
			{
				text.erase(text.begin() + index - 1, text.begin() + index);
				coord.X--;
				SetConsoleCursorPosition(h, coord);
			}
		}
		else
		{
			// writing regular text
			CONSOLE_SCREEN_BUFFER_INFO info;
			GetConsoleScreenBufferInfo(h, &info);
			COORD coord = info.dwCursorPosition;
			int index = coord.X - x - 1;
			if ((index >= 0) && (index < text.size()))
			{
				std::replace(text.begin() + index, text.begin() + index + 1, *(text.begin() + index), c->uChar.AsciiChar);
				coord.X++;
				SetConsoleCursorPosition(h, coord);
			}
			else
			{
				if (index <= width - 2)
					text.push_back(c->uChar.AsciiChar);
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
		case LEFT_KEY:
			coord.X--;
			if (coord.X > x)
				SetConsoleCursorPosition(h, coord);
			break;
		case RIGHT_KEY:
			coord.X++;
			if (coord.X < x + width)
				SetConsoleCursorPosition(h, coord);
			break;
		case DEL_KEY:
			int index = coord.X - x - 1;
			if (index < text.size())
				text.erase(text.begin() + index, text.begin() + index + 1);
			break;
		}
	}
}

void TextBox::clickWithMouse(HANDLE h, int _x, int _y)
{
	int maxX = x + GetText().size();
	COORD c = {_x, _y};
	if (_x > maxX)
		c.X = maxX + 1;
	SetConsoleCursorPosition(h, c);
}
