#pragma once

#include "CheckList.h"

class RadioBox : public CheckList
{
public:
	RadioBox(int x, int y, int width, vector<string> entries);
	virtual void keyPressed(HANDLE, KEY_EVENT_RECORD*);
	virtual void clickWithMouse(HANDLE, int x, int y);
private:
};




