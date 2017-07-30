#pragma once

#include "Panel.h"

class TextBox;
class Button;

class ComboBox : public Panel
{
public:
	ComboBox(int x, int y, int width, vector<string> entries);
	size_t GetSelectedIndex();
	void SetSelectedIndex(size_t index);
	virtual void draw(HANDLE);
	virtual bool canFocus();
	virtual void setFocus(HANDLE);
	virtual void keyPressed(HANDLE, KEY_EVENT_RECORD*);
	virtual bool contains(int x, int y);
	virtual void clickWithMouse(HANDLE, int x, int y);

private:
	vector<string> entries;
	size_t selectedIndex;
	int tempIndex;
	TextBox* text;
	Button* showList;
	bool shouldShowList;
};
