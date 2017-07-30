#pragma once

#include <Windows.h>

enum class ForegroundColor { Red, Blue, Green, Cyan, White, Black };
enum class BackgroundColor { Red, Blue, Green, Cyan, White, Black };
enum class BorderType { Single, Double, None };

#define LEFT_KEY 37
#define RIGHT_KEY 39
#define UP_KEY 38
#define DOWN_KEY 40
#define DEL_KEY 46

class Control
{
public:
	Control(int x, int y, int width);
	virtual ~Control();
	void setForeground(ForegroundColor);
	ForegroundColor getForeground();
	void setBackground(BackgroundColor);
	BackgroundColor getBackground();
	virtual void draw(HANDLE);
	void setBorder(BorderType);
	virtual bool canFocus();
	virtual void clickWithMouse(HANDLE, int x, int y);
	virtual bool contains(int x, int y);
	virtual void setFocus(HANDLE);
	virtual void keyPressed(HANDLE, KEY_EVENT_RECORD*);
	virtual bool shouldChangeFocusOnTab(HANDLE);
protected:
	DWORD getColor(ForegroundColor, BackgroundColor);
	int x;
	int y;
	int width;
	ForegroundColor foregroundColor;
	BackgroundColor backgroundColor;
	BorderType border;
};
