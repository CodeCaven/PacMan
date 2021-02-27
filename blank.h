#ifndef BLANK_H
#define BLANK_H
#include "board.h"


class Blank :public Board{

private:
	char blank;

public:
	Blank();
	char getChar();
};




#endif