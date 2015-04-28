#include "Aircraft.h"

#include "IA.h"
class IA;

Aircraft::Aircraft(int x, int y, int s, float speed, WORD color, Direction direction) : AnimeObject(x, y, s, speed, color, direction)
{
	setSpeed(speed);
	setFireFrequency(4);
	
	setShield(1);
	setDamage(0);

	_last_fire = GetTickCount(); // GetTicketCount é um contador que retorna em milisegundos desde a inicialização do windows.
}

int Aircraft::getDamage()
{
	return _damage;
}

void Aircraft::setDamage(int value)
{
	_damage = value;
}

int Aircraft::getShield()
{
	return _shield;
}

void Aircraft::setShield(int value)
{
	_shield = value;
}

/**
* Calcula a frequencia de tiro por segundos.
* Caso a frequencia de tiros seja > 1, realiza mais de 1 tiro por segundo.
* Caso a frequencia de tiro seja entre 0 e 1, realizar tiros acima de 1 segundo. Ex: 0.5, 1 tiro a cada 2 segundos.
*/
void Aircraft::setFireFrequency(float value)
{
	if (value > 0)
		_fire_frequency = value;
}

float Aircraft::getFireFrequency()
{
	return _fire_frequency;
}

bool Aircraft::canFire()
{
	return IA::isUPSAvailable(&_last_fire, _fire_frequency);
}

void Aircraft::hitShield()
{
	_shield -= 1;
}

Missile* Aircraft::fire()
{		
	int x;
	if (getMissileDirection() == Direction::UP)
		x = getX() - 1;
	else
		x = getX() + 1;

	return new Missile(x, getY(), getMissileSymbol(), getMissileSpeed(), getMissileColor(), getMissileDirection());
	
}