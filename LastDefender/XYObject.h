#ifndef _XYOBJECT_H
#define _XYOBJECT_H


#include <wtypes.h>
#include "Defs.h"


//
// Class to represent an object which has a position defined by X and Y.
//
//
class XYObject
{
public:	

	XYObject(int x, int y, char s, WORD color);

	int getX();	

	void setX(int value);

	int getY();

	void setY(int value);

	int getSymbol();

	void setSymbol(int value);

	WORD getColor();

	void setColor(WORD value);	

	bool isCollided(XYObject other);
	bool isCollided(XYObject *other);
		

protected:
	// X position
	int _x;
	// Y position
	int _y;
	// Symbol to represent the object
	char _symbol;
	// Color
	WORD _color;	
};

#endif
