#ifndef _AIRCRAFT_H 
#define _AIRCRAFT_H

#include <ctime>
#include "AnimeObject.h"
#include "Missile.h"
#include "Defs.h"

#define PROTECTOR_BULLET 248
#define PROTECTOR_BULLET_COLOR FOREGROUND_GREEN


/**
 * Class to represent an aircraft in the game.
 * 
 */
class Aircraft : public AnimeObject
{
	private: 		
		
		// Total strengh
		int _shield;
		// Damage received.
		int _damage;
		// shots per second.
		float _fire_frequency;
		// time of last fire
		DWORD _last_fire;

		struct tm* now()
		{
			time_t now;
			time(&now);
			return localtime(&now);
		}
		

	public:
		Aircraft(int x, int y, int s, float speed, WORD color, Direction direction);

		int getDamage();
		void setDamage(int value);

		int getShield();
		void setShield(int value);
		void hitShield();

		/**
		 * Calcula a frequencia de tiro por segundos.
		 * Caso a frequencia de tiros seja > 1, realiza mais de 1 tiro por segundo.
		 * Caso a frequencia de tiro seja entre 0 e 1, realizar tiros acima de 1 segundo. Ex: 0.5, 1 tiro a cada 2 segundos.
		 */
		void setFireFrequency(float value);

		float getFireFrequency();

		bool canFire();

		Missile* fire();

		virtual Direction getMissileDirection() = 0;
		virtual WORD getMissileSpeed() = 0;
		virtual WORD getMissileColor() = 0;
		virtual WORD getMissileSymbol() = 0;
};

#endif