#include "XYObject.h"
#include "IA.h"
class IA;

XYObject::XYObject(int x, int y, char s, WORD color)
{	
	_x = x;
	_y = y;
	_symbol = s;
	_color = color;	
}

int XYObject::getX()
{
	return _x;
}

void XYObject::setX(int value)
{
	_x = value;
}

int XYObject::getY()
{
	return _y;
}

void XYObject::setY(int value)
{
	_y = value;
}

int XYObject::getSymbol()
{
	return _symbol;
}

void XYObject::setSymbol(int value)
{
	_symbol = value;
}

WORD XYObject::getColor()
{
	return _color;
}

void XYObject::setColor(WORD value)
{
	this->_color = value;
}

bool XYObject::isCollided(XYObject other)
{
	return isCollided(&other);
}

bool XYObject::isCollided(XYObject *other)
{
	if (_y == other->_y)
	{
		return (_x == other->_x) ||
			(_x + 1 == other->_x) ||
			(_x - 1 == other->_x);
	}

	return false;
}
