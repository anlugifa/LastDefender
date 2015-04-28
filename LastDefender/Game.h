#ifndef _GAME_H
#define _GAME_H

#include <vector>
#include "XYObject.h"
#include "Protector.h"
#include "Alien.h"
#include "Missile.h"
#include "Console.h"

#include "Defs.h"
#include "InputControl.h"
#include "IA.h"

class Game
{	
	private:		
		bool _gameOver;
		bool _win;
		
		InputControl *_inputControl;
		IA *_ia;

		void gameLoop();
		void paintLifes();
		void painRemainingtAliens();

	public:
		Game();
		~Game();
		
		void gameOver();
		void win();
		void restart();
		
		void paintHistoryPage();
		void paintGameOver();
		bool paintRestart();
		
		void prepareStatusPanel();
		void paintStatusPanel();
		void eraseStatusPanel();

		bool processInput();	
		
		void start();
		void paint(int x, int y, int length, int valor, WORD color);
		void paintString(int x, int y, const char *str, WORD color);
		void paintXY(int x, int y, char valor, WORD color);
		void paintValueXY(int x, int y, long valor, WORD color);

		void paintXYObject(XYObject *o);
		void eraseXYObject(XYObject *o);
		
		template <typename  T>
		void paintObjects(std::vector<T *> *missiles);			

		void paintObjects();
		
		void paintProtector();

		void paint();
		
};

#endif