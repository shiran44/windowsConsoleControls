#pragma once

#include "Label.h"

struct MouseListener
{
	virtual void MousePressed(Control &control, int x, int y, bool isLeft) = 0;
};

class Button : public Label
{
public:
	Button(int x, int y, int width);
	~Button();
	virtual void clickWithMouse(HANDLE, int x, int y);
	void setMouseListener(MouseListener* mouseListener);

private:
	MouseListener* mouseListener;
};

