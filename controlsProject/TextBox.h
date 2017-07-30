#pragma once

#include "Control.h"
#include <string>

class TextBox : public Control
{
public:
	TextBox(int x, int y, int width);
	std::string GetText();
	void SetText(std::string);
	virtual void draw(HANDLE);
	virtual void setFocus(HANDLE);
	virtual void keyPressed(HANDLE, KEY_EVENT_RECORD*);
	virtual void clickWithMouse(HANDLE, int x, int y);

private:
	std::string text;
};



