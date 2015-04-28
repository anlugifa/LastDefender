#ifndef _MISSILE_H__
#define _MISSILE_H__

#include <wtypes.h>
#include "AnimeObject.h"
#include "Defs.h"

class Missile : public AnimeObject
{	
	public:		
		Missile(int x, int y, int s, WORD speed, WORD color, Direction direction);

		bool Missile::operator==(const Missile &other) const
		{
			// Check for self-assignment!
			if (this == &other)      // Same object?
				return true;        // Yes, so skip assignment, and just return *this.

			return this->_x == other._x && this->_y == other._y;
		}
};


#endif