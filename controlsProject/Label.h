#pragma once

#include "TextBox.h"

class Label : public TextBox
{
public:
	Label(int x, int y, int width);
	virtual bool canFocus();
private:
};
