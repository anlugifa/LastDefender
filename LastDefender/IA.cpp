#include "Defs.h"
#include "IA.h"

#include <algorithm>    // std::find_if
#include <vector>       // std::vector


IA::IA(Game *g)
{
	_game = g;

	_player = new SoundPlayer();
	_player->playMusic();

	srand(time(NULL));	
}

void IA::reset()
{
	_aliens_created = 0;
	_aliens_destroyed = 0;

	_time_last_alien_created = GetTickCount();

	_protector = new Protector(PROTECTOR_ROW, PROTECTOR_COL);	
	
	// recreate vector for missiles from protector
	if (_protectorMissiles == NULL) {
		_protectorMissiles = new std::vector<Missile *>();		
	}
	else{
		_protectorMissiles->clear();
	}

	// recreate vector for missiles from aliens
	if (_alienMissiles == NULL) {
		_alienMissiles = new std::vector<Missile *>();
	}
	else{
		_alienMissiles->clear();
	}

	// recreate vector for aliens
	if (_aliens == NULL) {
		_aliens = new std::vector<Alien *>();
	}
	else{
		_aliens->clear();
	}
	
}


Protector* IA::getProtector()
{
	return _protector;
}

int IA::remainingAliens()
{
	return ALIEN_TOTAL_MAX - _aliens_destroyed;
}

void IA::think()
{
	if (detectEnd())
		return;

	detectCollisions();
	createAliens();
	fireAliens();
}

bool IA::isUPSAvailable(DWORD *last_move, float frequency)
{
	if (frequency <= 0)
		return false;

	DWORD now = GetTickCount();
	double next_move_possible = *last_move + (1000 / frequency);
	if (now < next_move_possible)
	{
		return false;
	}

	*last_move = now;

	return true;
}


bool IA::detectEnd()
{
	// protector destruido
	if (_protector->getShield() <= 0)
	{
		_game->gameOver();
		return true;
	}

	//Todos aliens destruidos
	if (_aliens->size() == 0 && _aliens_created >= ALIEN_TOTAL_MAX)
	{
		_game->win();
		return true;
	}

	// Se algum alien chegou ao final, perdeu!
	std::vector<Alien *>::iterator iAlien;
	for (iAlien = _aliens->begin(); iAlien != _aliens->end(); ++iAlien)
	{
		Alien *a = *iAlien;
		if (a->getX() == PROTECTOR_ROW)
			_game->gameOver();
	}
	return false;
}

void IA::detectCollisions()
{
	// Missel contra missel
	detectMissile_x_Missile();
	
	// Missel protector x Alien
	detectMissile_x_Alien();

	// Missel Alien x Protector
	detectMissile_x_Protector();

	// Alien x Protector
	detectAlien_x_Protector();
}

void IA::detectMissile_x_Missile()
{
	std::vector<Missile *>::iterator iAlienM;
	std::vector<Missile *>::iterator iProtectM;

	for (iProtectM = _protectorMissiles->begin(); iProtectM != _protectorMissiles->end(); ++iProtectM)
	{
		Missile *pM = *iProtectM;
		for (iAlienM = _alienMissiles->begin(); iAlienM != _alienMissiles->end(); ++iAlienM)
		{
			Missile *aM = *iAlienM;

			/*if (*aM == *pM)*/
			if (aM->isCollided(pM))
			{
				_player->playExplosion();

				aM->kill();
				pM->kill();
			}
		}
	}
}

void IA::detectMissile_x_Alien()
{
	std::vector<Alien *>::iterator iAlien;
	std::vector<Missile *>::iterator iProtectM;

	for (iProtectM = _protectorMissiles->begin(); iProtectM != _protectorMissiles->end(); ++iProtectM)
	{
		Missile *pM = *iProtectM;

		const int x = pM->getX();
		const int y = pM->getY();

		
		for (iAlien = _aliens->begin(); iAlien != _aliens->end(); ++iAlien)
		{			
			Alien *a = *iAlien;
			
			if (pM->isCollided(a))
			{
				_player->playExplosion();

				pM->kill();

				a->hitShield();
				if (a->getShield() <= 0)
				{
					a->kill();
					_aliens_destroyed++;
				}
			}						
		}

		/*auto it = std::find_if(_aliens->begin(), _aliens->end(),
		[=](Alien *a) { return  a->getX() == x && a->getY() == y; });
		while (it != _aliens->end()) {
		it = std::find_if(++it, _aliens->end(),
		[=](Alien *a) { return  a->getX() == x && a->getY() == y; });
		}*/
	}
}


void IA::detectMissile_x_Protector()
{
	std::vector<Alien *>::iterator iAlien;
	std::vector<Missile *>::iterator iAliensM;

	for (iAliensM = _alienMissiles->begin(); iAliensM != _alienMissiles->end(); ++iAliensM)
	{
		Missile *aM = *iAliensM;

		if (aM->isCollided(_protector))
		{
			_player->playExplosion();
			aM->kill();
			_protector->hitShield();
			if (_protector->getShield() <= 0)
				_protector->kill();
		}
	}
}

void IA::detectAlien_x_Protector()
{
	std::vector<Alien *>::iterator iAlien;
	
	for (iAlien = _aliens->begin(); iAlien != _aliens->end(); ++iAlien)
	{
		Alien *a = *iAlien;

		if (a->isCollided(_protector))
		{
			_player->playExplosion();
			_game->gameOver();
			break;
		}
	}
}


void IA::createAliens()
{
	// numero de alien chegou ao limite não cria mais
	if (_aliens_created >= ALIEN_TOTAL_MAX)
		return;

	if (!isUPSAvailable(&_time_last_alien_created, ALIEN_CREATION_FREQUENCY))
		return;

	_aliens_created++;
	
	int y = 0;
	do
	{
		y = rand() % TOTAL_COLS;

	} while (contains(_aliensColumnStart, y));

	_aliensColumnStart.push_back(y);

	Alien *a = new Alien(y);	
	_aliens->push_back(a);
}

void IA::fireAliens()
{
	std::vector<Alien *>::iterator i;
	for (i = _aliens->begin(); i != _aliens->end(); ++i)
	{
		Alien *a = *i;

		if (a->canFire())
		{
			Missile *m = a->fire();
			if (m != NULL)
			{				
				m->move();
				_alienMissiles->push_back(m);

				_player->playAlienMissile();
			}
		}
	}	
}


void IA::keyLeftEvent()
{	
	_game->eraseXYObject((XYObject *)_protector);
	_protector->left();
}

void IA::keyRightEvent()
{	
	_game->eraseXYObject(_protector);
	_protector->right();
}

void IA::keyUpEvent()
{
	_game->eraseXYObject(_protector);
	_protector->up();
}

void IA::keyDownEvent()
{
	_game->eraseXYObject(_protector);
	_protector->down();
}

void IA::keySpaceEvent()
{
	if (_protector->canFire())
	{
		Missile *m = _protector->fire();		
		m->move();
		_protectorMissiles->push_back(m);		
				
		_player->playProtectorMissile();		
	}
}


std::vector<Missile *>* IA::getProtectorMissiles()
{
	return _protectorMissiles;
}

std::vector<Missile *>* IA::getAliensMissiles()
{
	return _alienMissiles;
}

std::vector<Alien *>* IA::getAliens()
{
	return _aliens;
}


template <typename T>
const bool IA::contains(std::vector<T> vec, const T item)
{
	if (std::find(vec.begin(), vec.end(), item) != vec.end())
		return true;

	return false;
}