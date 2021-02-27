#ifndef PAC_H
#define PAC_H
#include"board.h"

class Pacman :public Board{

private:
	char pac;
	int row;
	int col;
	int score;
	int lives;
	int level;


public:
	Pacman();
	char getChar();
	int getRow();
	int getCol();
	void setCol(int);
	void setRow(int);
	int getScore();
	int getLives();
	void setScore(int);
	void setLives(int);
	void reset(int&,int&);
	void setLevel();
	int getLevel();

};



#endif