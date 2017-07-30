#pragma once

#include "Panel.h"

class TextBox;
class Button;

class NumericBox : public Panel
{
public:
	NumericBox(int x, int y, int width, int min, int max);
	int GetValue();
	bool SetValue(int value); // returns whether the value is within bound
	void upOne();
	void downOne();
	virtual bool canFocus();
	virtual void draw(HANDLE);
	virtual void clickWithMouse(HANDLE, int x, int y);
private:
	int minValue;
	int maxValue;
	int value;
	TextBox* text;
	Button* up;
	Button* down;
};
