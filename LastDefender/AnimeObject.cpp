#include "AnimeObject.h"
#include "IA.h"
class IA;

AnimeObject::AnimeObject(int x, int y, int symbol, float speed, WORD color, Direction direction) : XYObject(x, y, symbol, color)
{
	_direction = direction;
	_isDead = false;
		
	_speed = speed;
	_last_move = GetTickCount();
}

Direction AnimeObject::getDirection()
{
	return _direction;
}

void AnimeObject::kill()
{
	_isDead = true;
}

bool AnimeObject::isDead()
{
	return _isDead;
}


float AnimeObject::getSpeed()
{
	return _speed;
}

// Set the speed. The value is the frequency the object will be updated in a second.
//Actually, this is the UPS.
void AnimeObject::setSpeed(float value)
{
	_speed = value;
}


bool AnimeObject::canMove()
{
	return IA::isUPSAvailable(&_last_move, getSpeed());
}

bool AnimeObject::move()
{
	bool outofbound = false;

	if (!canMove()) return false;

	switch (_direction)
	{
		case LEFT: return left();
		case RIGHT: return right();
		case DOWN: return down();
		case UP: return up();
	}

	return outofbound;
}

bool AnimeObject::right()
{
	_y += 1;
	if (_y > 79) {
		_y = 79;
		return true;
	}
	return false;
}

bool AnimeObject::left()
{
	_y -= 1;
	if (_y < 0)
	{
		_y = 0;
		return true;
	}

	return false;
}

bool AnimeObject::up()
{
	_x -= 1;
	if (_x < 0) {
		_x = 0;
		return true;
	}
	return false;
}

bool AnimeObject::down()
{
	_x += 1;
	if (_x > PROTECTOR_ROW) {
		_x = PROTECTOR_ROW;
		return true;
	}
	return false;
}
