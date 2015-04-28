#ifndef _PROTECTOR_H
#define _PROTECTOR_H

#include <wtypes.h>
#include <wincon.h>
#include "Aircraft.h"
#include "Defs.h"

class PosObject;
class Aircraft;

class Protector : public Aircraft
{

public:
	Protector(int x, int y);

	WORD getMissileSpeed();

	WORD getMissileColor();

	WORD getMissileSymbol();

	Direction getMissileDirection();

	bool up();
};


#endif
