#pragma once
#ifndef BORDER_H
#define BORDER_H
class Border
{
private:
	int x;
	int y;
	int width;
	int heigt;

public:
	Border();
	~Border();
	void solidBorder( int width , int heigt );


};

#endif 

