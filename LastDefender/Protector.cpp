#include "Protector.h"


Protector::Protector(int x, int y) : Aircraft(x, y, PROTECTOR_CRAFT, PROTECTOR_SPEED, PROTECTOR_COLOR, Direction::DOWN)
{	
	setFireFrequency(PROTECTOR_FIRE_FREQUENCY);
	setShield(PROTECTOR_SHIELD);
}

WORD Protector::getMissileSpeed()
{
	return PROTECTOR_MISSILE_SPEED;
}


WORD Protector::getMissileColor()
{
	return PROTECTOR_MISSILE_COLOR;
}

WORD Protector::getMissileSymbol()
{
	return PROTECTOR_MISSILE_SYMBOL;
}

Direction Protector::getMissileDirection()
{
	return Direction::UP;
}

bool Protector::up()
{
	_x -= 1;
	if (_x < 10) {
		_x = 10;
		return true;
	}

	return false;
}
