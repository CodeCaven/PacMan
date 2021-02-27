#ifndef GHOST_H
#define GHOST_H
#include"board.h"
#include <iostream>
using namespace std;

class Ghost :public Board{

private:
	char ghost;
	int row;
	int col;
	

public:
	Ghost(int,int);
	char getChar();
	void setRow(int);
	void setCol(int);
	int getRow();
	int getCol();
	void setChar(char);
	

};



#endif