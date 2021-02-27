#include "pacman.h"

Pacman::Pacman(){
	pac = 'P';
	row = 23;
	col = 15;
	score = 0;
	lives = 3;
	level = 1;
}
//Sets and gets
char Pacman::getChar(){
	return pac;
}

int Pacman::getRow(){
	return row;
}

int Pacman::getCol(){
	return col;
}

void Pacman::setRow(int newrow){
	row = newrow;
}

void Pacman::setCol(int newcol){
	col = newcol;
}

int Pacman::getLives(){
	return lives;
}

int Pacman::getScore(){
	return score;
}

void Pacman::setLives(int direct){
	if (direct == 1){
		lives++;
	}
	else {
		lives--;
	}
}

void Pacman::setScore(int up){
	score = score + up;
}

void Pacman::reset(int& row,int& col){
	setLives(-1);
	row = 23;
	col = 15;
	
}

void Pacman::setLevel(){
	level++;
}

int Pacman::getLevel(){
	return level;
}







