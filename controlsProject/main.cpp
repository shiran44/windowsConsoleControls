// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include "Button.h"
#include "NumericBox.h"
#include "ComboBox.h"
#include "RadioBox.h"
#include "MessageBox.h"

using namespace std;

Control* nextFocus(vector<Control*> controls, Control* currentFocus)
{
	if (currentFocus == NULL)
	{
		for (std::vector<Control*>::iterator it = controls.begin(); it != controls.end(); ++it)
			if ((*it)->canFocus())
				return *it;
	}
	bool found = false;
	for (std::vector<Control*>::iterator it = controls.begin(); it != controls.end(); ++it)
	{
		if (!found)
		{
			if (*it == currentFocus)
				found = true;
			continue;
		}
		if ((*it)->canFocus())
			return *it;
	}
	for (std::vector<Control*>::iterator it = controls.begin(); it != controls.end(); ++it)
		if ((*it)->canFocus())
			return *it;
	return NULL;
}

struct MyMouseListener : public MouseListener
{
	virtual void MousePressed(Control &control, int x, int y, bool isLeft)
	{
		exit(0);
	}
};

void main()
{
	vector<Control*> controls;
	Button* button = new Button(10, 20, 10);
	button->SetText("My button");
	button->setMouseListener(new MyMouseListener);
	button->setForeground(ForegroundColor::Red);
	button->setBackground(BackgroundColor::White);
	controls.push_back(button);
	TextBox* textBox = new TextBox(20, 10, 10);
	textBox->SetText("My text");
	controls.push_back(textBox);
	textBox = new TextBox(30, 15, 10);
	textBox->SetText("My new");
	controls.push_back(textBox);

	NumericBox* nb = new NumericBox(30, 25, 15, 200, 205);
	controls.push_back(nb);

	vector<string> entries;
	entries.push_back("First");
	entries.push_back("Second");
	entries.push_back("Third");
	entries.push_back("Forth");
	ComboBox* cb = new ComboBox(3, 5, 25, entries);
	controls.push_back(cb);

	RadioBox* cl = new RadioBox(30, 5, 25, entries);
	controls.push_back(cl);

	//MyMessageBox* msg = new MyMessageBox(30, 15, 25);
	//controls.push_back(msg);
	Control* currentFocus = nextFocus(controls, NULL);
	//set cursor position example
	INPUT_RECORD ir[5] = { 0 };
	DWORD num_read;

	srand(time(0));

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hinput = GetStdHandle(STD_INPUT_HANDLE);

	COORD c = { 7, 7 };

	SetConsoleCursorPosition(h, c);
	if (currentFocus)
		currentFocus->setFocus(h);
	SetConsoleMode(hinput, ENABLE_MOUSE_INPUT);

	/*printf("%c", '\xDA');
	for (short i = 0; i < 5; i++) {
		printf("%c", '\xC4');
	}
	printf("%c", '\xBF');
	for (short i = 1; i < 5; i++) {
		c = { 7, 7 + i };
		SetConsoleCursorPosition(h, c);
		printf("%c", '\xB3');
		c = { 13, 7 + i };
		SetConsoleCursorPosition(h, c);
		printf("%c", '\xB3');
	}
	c = { 7, 12 };
	SetConsoleCursorPosition(h, c);
	printf("%c", '\xc0');
	for (short i = 0; i < 5; i++) {
		printf("%c", '\xC4');
	}
	printf("%c", '\xd9');*/

	while (1) {
		for (std::vector<Control*>::iterator it = controls.begin(); it != controls.end(); ++it)
			(*it)->draw(h);

		ReadConsoleInput(hinput, ir, 5, &num_read);
		/*DWORD rndBG = rand() % 16;
		DWORD rndFG = rand() % 16;
		DWORD wAttr = rndFG | (rndBG << 4);

		SetConsoleTextAttribute(h, wAttr);*/
		if (num_read) {
			for (int i = 0; i<num_read; i++) {
				switch (ir[i].EventType) {
				case KEY_EVENT:
					if (ir[i].Event.KeyEvent.bKeyDown)
					{
						if (ir[i].Event.KeyEvent.uChar.AsciiChar == '\t')
						{
							if (currentFocus && currentFocus->shouldChangeFocusOnTab(h))
							{
								// change focus
								currentFocus = nextFocus(controls, currentFocus);
								if (currentFocus)
									currentFocus->setFocus(h);
							}
							else
							{
								if (currentFocus)
									currentFocus->keyPressed(h, &(ir[i].Event.KeyEvent));
							}
						}
						else
						{
							if (currentFocus)
								currentFocus->keyPressed(h, &(ir[i].Event.KeyEvent));
						}
					}
					/*printf("key %s it's virtual key code value %d\n",
						ir[i].Event.KeyEvent.bKeyDown ? "down" : "up",
						ir[i].Event.KeyEvent.wVirtualKeyCode);*/
					break;
				case MOUSE_EVENT:
					if (ir[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						COORD coordinates = ir[i].Event.MouseEvent.dwMousePosition;
						for (std::vector<Control*>::iterator it = controls.begin(); it != controls.end(); ++it)
						{
							if ((*it)->contains(coordinates.X, coordinates.Y))
							{
								(*it)->clickWithMouse(h, coordinates.X, coordinates.Y);
								break;
							}
						}
					}
					///////printf("mouse event\n");
					break;
				}
			}
		}

	}

	//set cursor size and visibility example

	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(h, &cci);
	/*
	//set foreground color

	DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(h, wAttr);

	printf("hello yellow ? world\n");

	CONSOLE_SCREEN_BUFFER_INFO cbi;

	GetConsoleScreenBufferInfo(h, &cbi);

	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE | BACKGROUND_GREEN;
	SetConsoleTextAttribute(h, wAttr2);

	printf("ugly background yellow foreground\n");

	GetConsoleScreenBufferInfo(h, &cbi);

	DWORD a = cbi.wAttributes | BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(h, a);


	//what color will that print ?
	printf("hello  ??? world\n");

	GetConsoleScreenBufferInfo(h, &cbi);
	a = cbi.wAttributes | COMMON_LVB_REVERSE_VIDEO;
	SetConsoleTextAttribute(h, a);

	printf("and now ?");

	getchar();
	*/

	//last: ReadConsoleInput
}
