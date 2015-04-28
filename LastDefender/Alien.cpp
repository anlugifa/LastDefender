#include "Alien.h"

Alien::Alien(int y) : Aircraft(0, y, ALIEN_CRAFT, ALIEN_SPEED, ALIEN_COLOR, Direction::DOWN)
{	
	setFireFrequency(ALIEN_FIRE_FREQUENCY);
	setShield(ALIEN_SHIELD);
}

WORD Alien::getMissileSpeed()
{
	return ALIEN_MISSILE_SPEED;
}

WORD Alien::getMissileColor()
{
	return ALIEN_MISSILE_COLOR;
}

WORD Alien::getMissileSymbol()
{
	return ALIEN_MISSILE_SYMBOL;
}

Direction Alien::getMissileDirection()
{
	return Direction::DOWN;
}


