#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "Console.h"
#include <SFML/Audio.hpp>

#include "Game.h"

int main(int argc, char **argv) 
{	
	Game game;		
	game.start();
	
	exit(0);
}