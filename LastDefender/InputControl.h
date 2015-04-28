#ifndef _INPUTCONT_H
#define _INPUTCONT_H

#include "IA.h"

class IA;

class InputControl {

public:
	InputControl(IA *ia);

	bool keydown(int key);

	bool processInput();

private:
	IA *_ia;
};

#endif