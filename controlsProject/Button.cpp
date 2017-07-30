#include "Button.h"

Button::Button(int x, int y, int width) :
	Label(x, y, width), mouseListener(NULL)
{
}

Button::~Button()
{
	if (mouseListener != NULL)
		delete mouseListener;
}

void Button::clickWithMouse(HANDLE, int x, int y)
{
	if (mouseListener != NULL)
		mouseListener->MousePressed(*this, x, y, true);
}

void Button::setMouseListener(MouseListener* newMouseListener)
{
	mouseListener = newMouseListener;
}

