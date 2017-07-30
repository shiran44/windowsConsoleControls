#pragma once

#include "Panel.h"

#ifdef MessageBox
#undef MessageBox
#endif MessageBox

class Label;
class Button;

class MyMessageBox : public Panel
{
public:
	MyMessageBox(int x, int y, int width, string message);
	virtual void draw(HANDLE);
	string getClickedButton();
	void setClickedButton(string);

private:
	Label* text;
	Button* okButton;
	Button* cancelButton;
	string clickedButton;
};


