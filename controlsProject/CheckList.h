#pragma once

#include "Panel.h"

class CheckList : public Panel
{
public:
	CheckList(int x, int y, int width, vector<string> entries);
	vector<size_t> GetSelectedIndices();
	void SelectIndex(size_t index);
	void DeselectIndex(size_t index);
	virtual void draw(HANDLE);
	virtual bool canFocus();
	virtual void setFocus(HANDLE);
	virtual void keyPressed(HANDLE, KEY_EVENT_RECORD*);
	virtual bool contains(int x, int y);
	virtual void clickWithMouse(HANDLE, int x, int y);
	virtual bool shouldChangeFocusOnTab(HANDLE);
	bool AddSelectedItem(string item);
	bool RemoveSelectedItem(string item);
protected:
	vector<string> entries;
	vector<size_t> selectedIndices;
	int tempIndex;
};

