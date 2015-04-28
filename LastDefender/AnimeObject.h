#ifndef _ANIMEOBJECT_H
#define _ANIMEOBJECT_H

#include "Defs.h"
#include "XYObject.h"

class AnimeObject : public XYObject
{
public:
	AnimeObject(int x, int y, int symbol, float speed, WORD color, Direction direction);

	Direction getDirection();

	void kill();

	bool isDead();

	float getSpeed();

	// Set the speed. The value is the frequency the object will be updated in a second.
	//Actually, this is the UPS.
	void setSpeed(float value);

	bool canMove();

	virtual bool move();

	virtual bool right();

	virtual bool left();

	virtual bool up();

	virtual bool down();

private:
	bool _isDead;
	Direction _direction;

	// The speed object
	float _speed;

	// save milliseconds of last move
	DWORD _last_move;
};

#endif