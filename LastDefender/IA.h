#ifndef _IA_H
#define _IA_H

#include <vector>
#include "Missile.h"
#include "Protector.h"
#include "Alien.h"
#include "Game.h"

#include "SoundPlayer.h"

class Game;

class IA
{
public: 
	IA(Game *g);

	void reset();
	void think();
	void detectCollisions();
	bool detectEnd();
	void createAliens();
	void fireAliens();
	int remainingAliens();

	void detectMissile_x_Missile();
	void detectMissile_x_Alien();
	void detectMissile_x_Protector();
	void detectAlien_x_Protector();

	void keyLeftEvent();
	void keyRightEvent();
	void keyUpEvent();
	void keyDownEvent();
	void keySpaceEvent();

	std::vector<Missile *>* getProtectorMissiles();
	std::vector<Missile *>* getAliensMissiles();
	std::vector<Alien *>* getAliens();
	
	Protector *getProtector();
	
	static bool isUPSAvailable(DWORD *last_move, float frequency);
	
	// Função para checar presença de objeto no vetor generico
	template <typename T>
	const bool contains(std::vector<T> Vec, T Element);

private:
	
	int _aliens_created, _aliens_destroyed;
	DWORD _time_last_alien_created;

	Game *_game;
	Protector *_protector;
	std::vector<Missile *> *_protectorMissiles = NULL;
	std::vector<Missile *> *_alienMissiles = NULL;
	std::vector<Alien *> *_aliens = NULL;
	std::vector<int> _aliensColumnStart;

	SoundPlayer *_player;
};

#endif
