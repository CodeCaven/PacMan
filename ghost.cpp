#include "ghost.h"

Ghost::Ghost(int row,int col){
	Ghost::row = row;
	Ghost::col = col;
	ghost = 'G';
}

char Ghost::getChar(){
		return ghost;
}

void Ghost::setRow(int row){
	Ghost::row = row;
}

void Ghost::setCol(int col){
	Ghost::col = col;
}

int Ghost::getRow(){
	return row;
}

int Ghost::getCol(){
	return col;
}

void Ghost::setChar(char run){
	ghost = run;
	
}

