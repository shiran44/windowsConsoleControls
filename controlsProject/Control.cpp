#include "Control.h"
#include <stdio.h>

Control::Control(int _x, int _y, int _width) :
	x(_x), y(_y), width(_width), border(BorderType::None)
{
	setBorder(BorderType::Single);
	backgroundColor = BackgroundColor::Black;
	foregroundColor = ForegroundColor::White;
}

Control::~Control()
{
}

void Control::setForeground(ForegroundColor color)
{
	foregroundColor = color;
}

ForegroundColor Control::getForeground()
{
	return foregroundColor;
}

void Control::setBackground(BackgroundColor color)
{
	backgroundColor = color;
}

BackgroundColor Control::getBackground()
{
	return backgroundColor;
}

bool Control::shouldChangeFocusOnTab(HANDLE)
{
	return true;
}

void Control::draw(HANDLE h)
{
	DWORD wAttr = getColor(foregroundColor, backgroundColor);

	SetConsoleTextAttribute(h, wAttr);
	if (border == BorderType::None)
		return;
	COORD c = { SHORT(x), SHORT(y - 1) };

	SetConsoleCursorPosition(h, c);
	printf("%c", '\xDA');
	for (short i = 0; i < width - 1; i++) {
		printf("%c", '\xC4');
	}
	printf("%c", '\xBF');
	c = { SHORT(x), SHORT(y) };
	SetConsoleCursorPosition(h, c);
	printf("%c", '\xB3');
	c = { SHORT(x + width), SHORT(y) };
	SetConsoleCursorPosition(h, c);
	printf("%c", '\xB3');
	/*for (short i = 1; i < height; i++) {
		c = { SHORT(x), SHORT(y + i) };
		SetConsoleCursorPosition(h, c);
		printf("%c", '\xB3');
		c = { SHORT(x + width), SHORT(y + i) };
		SetConsoleCursorPosition(h, c);
		printf("%c", '\xB3');
	}*/
	c = { SHORT(x), SHORT(y + 1) };
	SetConsoleCursorPosition(h, c);
	printf("%c", '\xc0');
	for (short i = 0; i < width - 1; i++) {
		printf("%c", '\xC4');
	}
	printf("%c", '\xd9');
}

void Control::setBorder(BorderType newBorder)
{
	border = newBorder;
}

bool Control::canFocus()
{
	return true;
}

void Control::clickWithMouse(HANDLE, int x, int y)
{
}

DWORD Control::getColor(ForegroundColor fgColor, BackgroundColor bgColor)
{
	DWORD rndBG = 0;
	DWORD rndFG = 0;
	DWORD color;
	switch (fgColor)
	{
	case ForegroundColor::Red:
		rndFG = FOREGROUND_RED;
		break;
	case ForegroundColor::Blue:
		rndFG = FOREGROUND_BLUE;
		break;
	case ForegroundColor::Green:
		rndFG = FOREGROUND_GREEN;
		break;
	case ForegroundColor::Cyan:
		rndFG = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE;
		break;
	case ForegroundColor::Black:
		rndFG = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		break;
	case ForegroundColor::White:
		rndFG = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		break;
	}

	switch (bgColor)
	{
	case BackgroundColor::Red:
		rndBG = BACKGROUND_RED;
		break;
	case BackgroundColor::Blue:
		rndBG = BACKGROUND_BLUE;
		break;
	case BackgroundColor::Green:
		rndBG = BACKGROUND_GREEN;
		break;
	case BackgroundColor::Cyan:
		rndBG = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_BLUE;
		break;
	case BackgroundColor::Black:
		rndBG = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
		break;
	case BackgroundColor::White:
		rndBG = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
		break;
	}
	color = rndFG | (rndBG << 4);
	return color;
}

bool Control::contains(int _x, int _y)
{
	if ((_x >= x) && (_x <= x + width) && (_y >= y) && (_y <= y + 1))
		return true;
	return false;
}

void Control::setFocus(HANDLE)
{
}

void Control::keyPressed(HANDLE, KEY_EVENT_RECORD*)
{
}


