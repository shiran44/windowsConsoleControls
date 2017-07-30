#include "MessageBox.h"
#include "Label.h"
#include "Button.h"

struct OKMouseListener : public MouseListener
{
public:
	OKMouseListener(MyMessageBox* _messageBox) : messageBox(_messageBox) {}
	virtual void MousePressed(Control &control, int x, int y, bool isLeft)
	{
		if (messageBox != NULL)
			messageBox->setClickedButton("OK");
	}

private:
	MyMessageBox* messageBox;
};

struct CancelMouseListener : public MouseListener
{
public:
	CancelMouseListener(MyMessageBox* _messageBox) : messageBox(_messageBox) {}
	virtual void MousePressed(Control &control, int x, int y, bool isLeft)
	{
		if (messageBox != NULL)
			messageBox->setClickedButton("Cancel");
	}

private:
	MyMessageBox* messageBox;
};


MyMessageBox::MyMessageBox(int x, int y, int width, string message) : Panel(x, y, width)
{
	text = new Label(x + width / 4, y + 5, width / 2);
	text->SetText(message);
	okButton = new Button(x + width / 8, y + 10, 4);
	okButton->SetText("OK");
	okButton->setMouseListener(new OKMouseListener(this));
	cancelButton = new Button(x + 4 * width / 6, y + 10, 8);
	cancelButton->SetText("Cancel");
	cancelButton->setMouseListener(new CancelMouseListener(this));
	AddControl(text);
	AddControl(okButton);
	AddControl(cancelButton);
}

void MyMessageBox::draw(HANDLE h)
{
	DWORD wAttr = getColor(foregroundColor, backgroundColor);

	SetConsoleTextAttribute(h, wAttr);
	if (!clickedButton.empty())
	{
		// erase everything
		int height = 16;
		for (short i = 0; i < height; i++) {
			COORD c = { SHORT(x - 1), SHORT(y + i - 1) };

			SetConsoleCursorPosition(h, c);
			for (short j = 0; j < width + 2; j++)
				printf(" ");
		}
		return;
	}
	COORD c = { SHORT(x), SHORT(y - 1) };

	SetConsoleCursorPosition(h, c);
	printf("%c", '\xDA');
	for (short i = 0; i < width - 1; i++) {
		printf("%c", '\xC4');
	}
	printf("%c", '\xBF');
	c = { SHORT(x), SHORT(y) };
	SetConsoleCursorPosition(h, c);
	printf("%c", '\xB3');
	c = { SHORT(x + width), SHORT(y) };
	SetConsoleCursorPosition(h, c);
	printf("%c", '\xB3');
	int height = 14;
	for (short i = 1; i < height; i++) {
	c = { SHORT(x), SHORT(y + i) };
	SetConsoleCursorPosition(h, c);
	printf("%c", '\xB3');
	c = { SHORT(x + width), SHORT(y + i) };
	SetConsoleCursorPosition(h, c);
	printf("%c", '\xB3');
	}
	c = { SHORT(x), SHORT(y + height) };
	SetConsoleCursorPosition(h, c);
	printf("%c", '\xc0');
	for (short i = 0; i < width - 1; i++) {
		printf("%c", '\xC4');
	}
	printf("%c", '\xd9');

	drawControls(h);
}

string MyMessageBox::getClickedButton()
{
	return clickedButton;
}
void MyMessageBox::setClickedButton(string buttunName)
{
	clickedButton = buttunName;
}
