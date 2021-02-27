#ifndef GAME_H
#define GAME_H
#include "blank.h"
#include "smallpill.h"
#include "largepill.h"
#include "pacman.h"
#include "ghost.h"
#include "io.h"


class Game{

private:
	static int const ROW = 31;
	static int const COL = 28;
	Board* board[ROW][COL];
	Board* display;
	Board* brick;
	Blank* blank;
	Smallpill* smallpill;
	Largepill* largepill;
	Pacman* pacman;
	Ghost* pinkey;
	Ghost* inkey;
	Ghost* blinkey;
	Ghost* clyde;
	IO* input;
	int abstract[ROW][COL];
	// singleton implementation
	Game();
	static Game* game;

public:
	void startAbstract();
	void startBoard();
	void gameLogic();
	void ghostMove(int&, int&, int&, bool&,int ,int,bool,int,bool,int&);
	void AI(int&, int&, int&,int ,int,int,int&);
	void check(int&, int&, bool&);
	void resetGhost(int&, int&, int&,bool&,Ghost*&,int);
	void attackCheck(int&, bool&, Ghost*&);
	void cleanUp();
	bool levelCheck();
	void setBoard();
	static Game* getGame();
	

};


#endif