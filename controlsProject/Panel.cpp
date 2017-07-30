#include "Panel.h"

Panel::Panel(int x, int y, int width) :
	Control(x, y, width)
{

}

Panel::~Panel()
{
	for (std::vector<Control*>::iterator it = controls.begin(); it != controls.end(); ++it)
		delete *it;
}

void Panel::AddControl(Control* control)
{
	controls.push_back(control);
}

void Panel::draw(HANDLE h)
{
	DWORD wAttr = getColor(foregroundColor, backgroundColor);

	SetConsoleTextAttribute(h, wAttr);
	Control::draw(h);
	drawControls(h);
}

bool Panel::contains(int _x, int _y)
{
	for (std::vector<Control*>::iterator it = controls.begin(); it != controls.end(); ++it)
		if ((*it)->contains(_x, _y))
			return true;
	return false;
}

void Panel::drawControls(HANDLE h)
{
	for (std::vector<Control*>::iterator it = controls.begin(); it != controls.end(); ++it)
		(*it)->draw(h);
}

void Panel::clickWithMouse(HANDLE h, int _x, int _y)
{
	for (std::vector<Control*>::iterator it = controls.begin(); it != controls.end(); ++it)
	{
		if ((*it)->contains(_x, _y))
		{
			(*it)->clickWithMouse(h, _x, _y);
			break;
		}
	}
}
