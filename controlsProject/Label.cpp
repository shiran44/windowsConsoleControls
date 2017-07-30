#include "Label.h"


Label::Label(int x, int y, int width) : TextBox(x, y, width)
{

}

bool Label::canFocus()
{
	return false;
}
