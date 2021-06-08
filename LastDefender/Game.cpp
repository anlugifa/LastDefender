#include <conio.h>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include "Game.h"
#include "Console.h"
#include "XYObject.h"
#include "AnimeObject.h"


Game::Game()
{	
	_gameOver = false;
	_win = false;
	
	_ia = new IA(this);
	_inputControl = new InputControl(_ia);	
}

Game::~Game()
{
	delete _ia;
	delete _inputControl;
}


void Game::paint(int x, int y, int length, int valor, WORD color)
{
	for (int i = y; i <= length; i++)		
		this->paintXY(x, i, color, valor);
}

void Game::paintString(int x, int y, const char *str, WORD color)
{	
	mostratexto(y, x, str, color);
}


void Game::paintXY(int x, int y, char valor, WORD color)
{	
	mostrar(y, x, color, valor);
}


void Game::paintValueXY(int x, int y, long valor, WORD color)
{
	mostrarC(y, x, color, valor);
}

void Game::prepareStatusPanel()
{
	int linha_inicial = 22;
	int linha_final = 24;

	char row2[81];
	char row3[80];
	sprintf(row2, " Vidas do Guardiao:                                   Naves Restantes:          \0");
	sprintf(row3, "                                                                               \0");

	paintString(BEGIN_STATUS_ROW, 0, EMPTY_ROW, BACKGROUND_INTENSITY | FOREGROUND_BLUE);
	paintString(PROTECTOR_LIFE_ROW, 0, row2, BACKGROUND_INTENSITY | FOREGROUND_BLUE);
	paintString(NUM_SHIPS_ROW, 0, row3, BACKGROUND_INTENSITY | FOREGROUND_BLUE);
}

void Game::paintLifes()
{
	int p_shield = _ia->getProtector()->getShield();

	char lifes[12];
	for (int i = 0; i < (PROTECTOR_SHIELD * 2) + 1; i++)
	{
		if (p_shield*2 > i && (i % 2==0))
			lifes[i] = PROTECTOR_CRAFT;
		else
			lifes[i] = ' ';
	}

	lifes[11] = '\0';

	paintString(PROTECTOR_LIFE_ROW, 21, lifes, BACKGROUND_INTENSITY | FOREGROUND_BLUE);
}

void Game::painRemainingtAliens()
{
	int aliens = _ia->remainingAliens();

	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << aliens;
	std::string str = ss.str();
	const char *texto = str.c_str();

	paintString(PROTECTOR_LIFE_ROW, 71, texto, BACKGROUND_INTENSITY | FOREGROUND_BLUE);
}

void Game::paintStatusPanel()
{		
	paintLifes();
	painRemainingtAliens();
}

void Game::paintGameOver()
{
	if (_win)
	{
		paintString(ROW_GAMEOVER, COL_GAMEOVER, WIN_STRING, FOREGROUND_GREEN);
	}
	else
	{
		paintString(ROW_GAMEOVER, COL_GAMEOVER, LOSE_STRING, FOREGROUND_RED);
	}
}


bool Game::paintRestart()
{
	char c[2];

	paintString(ROW_RESTART, COL_GAMEOVER, RESTART_STRING, FOREGROUND_CYAN);
		
	std::cin.clear();	
	scanf("%1c", &c);
	
	if (c[0] == 'Y' || c[0] == 'y' || c[0] == 's')
		return true;

	return false;
}



void Game::eraseStatusPanel()
{
	int linha_inicial = 23;
	int linha_final = 25;

	paintString(linha_inicial++, 0, EMPTY_ROW, BACKGROUND_BLACK);
	paintString(linha_inicial++, 0, EMPTY_ROW, BACKGROUND_BLACK);
	paintString(linha_inicial++, 0, EMPTY_ROW, BACKGROUND_BLACK);
	
}

void Game::paintXYObject(XYObject *o)
{	
	paintXY(o->getX(), o->getY(), o->getSymbol(), o->getColor());
}

void Game::eraseXYObject(XYObject *o)
{
	paintXY(o->getX(), o->getY(), ' ', BACKGROUND_BLACK);
}

void Game::paintHistoryPage()
{
	int linha_inicial = 15;
	int coluna_inicial = 10;
	
	clrscr();

	char history[10][70] = 
	{
	//                                                                    \0
		"Numa epoca onde poucos acreditavam na humanidade...\n\0",
		"Onde a esperanca estava completamente perdida...\n\0",
		"Onde o medo imperava sobre os coracoes...\n\0",
		"Onde a vida de cada ser-humano era ameacada por alieniginas...\n\0",
		" \n\0"
		"Surge uma ultima esperança...\n\0",
		"A especie humana esta nas maos do ultimo guardiao...\n\0",
		"Cerca de 20 naves alieniginas sobraram da frota dos URBS...\n\0",
		"Elas tentarao de todas as formas entrar na atmosfera terrestre.\n\0",
		"Cabe ao guardiao impedi-los e acabar com a ameaca..\n\0",

	};
	
	for (int i = 0; i < 10; i++)
	{		
		int k = 0;
		for (int j = i; j >= 0; j--)
		{
			paintString(linha_inicial - j, coluna_inicial, history[k++], FOREGROUND_CYAN);
		}

		Sleep(600);

		if (i < 9)
		{
			for (int j = i; j >= 0; j--)
			{
				paintString(linha_inicial - j, coluna_inicial, "                                                                    ", BACKGROUND_BLACK);
			}
		}
		
	}

	getche();
	// TODO: Fazer opçao de menu para Iniciar o jogo.
}

template <typename T>
void Game::paintObjects(std::vector<T *> *objects)
{		
	std::vector<T*>::iterator i;
	for (i = objects->begin(); i != objects->end(); ++i)
	{	
		T *o = *i;
				
		eraseXYObject(o);
		if (o->isDead() || o->move())
		{			
			o->kill();			
		}
		else
		{
			paintXYObject(o);
		}

		(*i) = o;
	}
	
	// delete dead missiles
	auto elements = std::remove_if(
							objects->begin(),
							objects->end(),
							[](T *o) { return o->isDead() == true; });

	objects->erase(elements, objects->end());
}


void Game::paintProtector()
{	
	paintXYObject(_ia->getProtector());
}

void Game::paintObjects()
{
	paintProtector();	
	paintObjects(_ia->getProtectorMissiles());
	paintObjects(_ia->getAliensMissiles());
	paintObjects(_ia->getAliens());
}

/**
 * 
 */
bool Game::processInput()
{
	return _inputControl->processInput();
}

void Game::paint()
{
	paintStatusPanel();
	paintObjects();	

	// Esconde o cursor na ultima linha e ultima coluna
	gotoxy(80, 24);
}

void Game::gameOver()
{
	_gameOver = true;
}

void Game::win()
{
	_win = true;
	_gameOver = true;
}

void Game::restart()
{
	_win = false;
	_gameOver = false;

	_ia->reset();
}

void Game::gameLoop()
{
	bool reiniciar = true;

	while (reiniciar)
	{
		clrscr();

		restart();

		prepareStatusPanel();

		while (processInput() && !_gameOver)
		{
			_ia->think();

			paint();

			Sleep(34);
		}		
		
		paintGameOver();
		reiniciar = paintRestart();
	}
}

void Game::start()
{	
	this->paintHistoryPage();
	this->gameLoop();
}