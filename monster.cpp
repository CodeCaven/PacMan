#include "monster.h"

// constructor
char Monster::getChar(){
		return block;
}

// pure virtual function
void Monster::setChar(char run){
	block = run;
}

// set and get functions
void Monster::setRow(int row){
	Monster::row = row;
}

void Monster::setCol(int col){
	Monster::col = col;
}

int Monster::getRow(){
	return row;
}

int Monster::getCol(){
	return col;
}



