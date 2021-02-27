#ifndef MONSTER_H
#define MONSTER_H
#include"board.h"

// child class to Board and parent class to Ghost and Pacman
class Monster:public Board{

protected:
	int row;
	int col;

public:
	// Abstract Base Class
	virtual char getChar() = 0;
	void setRow(int row);
	void setCol(int col);
	void setChar(char run);
	int getRow();
	int getCol();
};

#endif