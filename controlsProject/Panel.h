#pragma once

#include "Control.h"
#include <vector>
using namespace std;

class Panel : public Control
{
public:
	Panel(int x, int y, int width);
	~Panel();
	void AddControl(Control*);
	virtual void draw(HANDLE);
	virtual void clickWithMouse(HANDLE, int x, int y);
	virtual bool contains(int x, int y);
protected:
	void drawControls(HANDLE);
private:
	vector<Control*> controls;
};


