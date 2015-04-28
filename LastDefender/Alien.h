#ifndef _ALIEN_H
#define _ALIEN_H

#include <wtypes.h>
#include <wincon.h>
#include "Aircraft.h"
#include "Defs.h"

class PosObject;
class Aircraft;

class Alien : public Aircraft
{

public:
	Alien(int y);

	WORD getMissileSpeed();
	WORD getMissileColor();
	WORD getMissileSymbol();
	Direction getMissileDirection();
};


#endif