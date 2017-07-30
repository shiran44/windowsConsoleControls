#include "NumericBox.h"
#include "TextBox.h"
#include "Button.h"

struct UpMouseListener : public MouseListener
{
public:
	UpMouseListener(NumericBox* _numericBox) : numericBox(_numericBox) {}
	virtual void MousePressed(Control &control, int x, int y, bool isLeft)
	{
		if (numericBox != NULL)
			numericBox->upOne();
	}

private:
	NumericBox* numericBox;
};

struct DownMouseListener : public MouseListener
{
public:
	DownMouseListener(NumericBox* _numericBox) : numericBox(_numericBox) {}
	virtual void MousePressed(Control &control, int x, int y, bool isLeft)
	{
		if (numericBox != NULL)
			numericBox->downOne();
	}

private:
	NumericBox* numericBox;
};


NumericBox::NumericBox(int x, int y, int width, int _min, int _max) :
	Panel(x, y, width), minValue(_min), maxValue(_max), value(_min)
{
	text = new TextBox(x + 3, y, width - 5);
	char buf[50];
	sprintf(buf, "%d", value);
	text->SetText(buf);
	text->setBorder(BorderType::None);
	up = new Button(x + 1, y, 1);
	up->setBorder(BorderType::None);
	up->SetText("+");
	up->setMouseListener(new UpMouseListener(this));
	down = new Button(x + width - 2, y, 1);
	down->setBorder(BorderType::None);
	down->SetText("-");
	down->setMouseListener(new DownMouseListener(this));
	AddControl(text);
	AddControl(up);
	AddControl(down);
}

bool NumericBox::canFocus()
{
	return false;
}

int NumericBox::GetValue()
{
	return value;
}

bool NumericBox::SetValue(int newValue)
{
	if ((newValue >= minValue) && (newValue <= maxValue))
	{
		value = newValue;
		char buf[50];
		sprintf(buf, "%d", value);
		text->SetText(buf);
		return true;
	}
	return false;
}

void NumericBox::upOne()
{
	SetValue(GetValue() + 1);
}

void NumericBox::downOne()
{
	SetValue(GetValue() - 1);
}

void NumericBox::draw(HANDLE h)
{
	DWORD wAttr = getColor(foregroundColor, backgroundColor);

	SetConsoleTextAttribute(h, wAttr);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(h, &info);
	COORD coord = info.dwCursorPosition;
	Panel::draw(h);
	SetConsoleCursorPosition(h, coord);
}

void NumericBox::clickWithMouse(HANDLE h, int _x, int _y)
{
	if (up->contains(_x, _y))
	{
		up->clickWithMouse(h, _x, _y);
		return;
	}

	if (down->contains(_x, _y))
	{
		down->clickWithMouse(h, _x, _y);
		return;
	}
}

