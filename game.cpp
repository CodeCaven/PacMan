#include "game.h"


Game::Game(){
	blank = new Blank;
	brick = new Board;
	smallpill = new Smallpill;
	largepill = new Largepill;
	pacman = new Pacman;
	pinkey = new Ghost(13,13);
	inkey = new Ghost(13,
		14);
	blinkey = new Ghost(13,15);
	clyde = new Ghost(13,16);
	input = new IO;
	startAbstract();
	setBoard();
}

void Game::gameLogic(){
	int row = pacman->getRow();
	int col = pacman->getCol();

	int prow = pinkey->getRow();
	int pcol = pinkey->getCol();
	bool pbool = false;
	int plast = 0;
	

	int irow = inkey->getRow();
	int icol = inkey->getCol();
	bool ibool = false;
	int ilast = 0;
	

	int brow = blinkey->getRow();
	int bcol = blinkey->getCol();
	bool bbool = false;
	int blast = 0;
	

	int crow = clyde->getRow();
	int ccol = clyde->getCol();
	bool cbool = false;
	int clast = 0;
	
	
	int clock = 0;
	bool reset = false;
	bool next = true;
	int beforerow = 0;
	int beforecol = 0;
	bool level = false;
	

	bool pattack = false;
	int pattacktime = 0;
	bool iattack = false;
	int iattacktime = 0;
	bool battack = false;
	int battacktime = 0;
	bool cattack = false;
	int cattacktime = 0;

	int pAIlast = 0;
	int iAIlast = 0;
	int bAIlast = 0;
	int cAIlast = 0;

	int cpos = 10;
	int ppos = 11;
	int ipos = 12;
	int bpos = 13;

	// passing arrays
	// missing lil gs
	// improve AI silly stuck left wall
	// clock logic
	// better display
	// levels with lives up and infinite gameplay wrong,leaving gs at base level 2 
	// cherries fruit powerups
	// logic step through


	input->title("PACMAN");
	input->setName();
	input->pacPlay();
	input->pacDisplay(board, ROW, COL, pacman, abstract);
	
	
	while (pacman->getLives() > 0){
		clock++;
		next = true;
		
		//set pacmans last position to a blank
		
		abstract[row][col] = 0;
		//get pacmans next position 
		beforerow = row;
		beforecol = col;
		do{
			row = beforerow;
			col = beforecol;
			input->input(row, col);
		} while (abstract[row][col] == 4);

		// ghosts next positions and set them one by one..ghost move sets last position  and the next

		ghostMove(prow, pcol, plast, pbool,row ,col,pattack,pattacktime,next,pAIlast);
		     if (pattack == true){
			     abstract[prow][pcol] = 7;
		     }
		     else if (pattack == false){
			     abstract[prow][pcol] = 11;
		}

		if (clock > 5){
			ghostMove(irow, icol, ilast, ibool, row, col, iattack, iattacktime,next,iAIlast);
			if (iattack == true){
			abstract[irow][icol] = 8;
			}
			else if (iattack == false){
			abstract[irow][icol] = 12;
			}
			
		}

		if (clock > 10){
			ghostMove(brow, bcol, blast, bbool, row, col, battack, battacktime,next,bAIlast);
			if (battack == true){
			abstract[brow][bcol] = 9;
			}
			else if (battack == false){
			abstract[brow][bcol] = 13;
			}	
		}

		if (clock > 15){
			ghostMove(crow, ccol, clast,cbool, row, col, cattack, cattacktime,next,cAIlast);
			if (cattack == true){
			abstract[crow][ccol] = 6;
			}
			else if (cattack == false){
			abstract[crow][ccol] = 10;
			}
		}

		// conditional checks
		if (abstract[row][col] > 9 || abstract[beforerow][beforecol] > 9 ){
			pacman->reset(row, col);
			reset = true;
			cout << '\a' << endl;
		}
		else if (abstract[row][col] == 2){
			pacman->setScore(10);
		}
		else if (abstract[row][col] == 3){
			pacman->setScore(50);
			pattack = true;
			pattacktime = 0;
			pinkey->setChar('g');
			iattack = true;
			iattacktime = 0;
			inkey->setChar('g');
			battack = true;
			battacktime = 0;
			blinkey->setChar('g');
			cattack = true;
			cattacktime = 0;
			clyde->setChar('g');
		}
		else if (abstract[row][col] == 7 || abstract[beforerow][beforecol] == 7){
			if (plast == 2){
				pacman->setScore(10);
			}
			pacman->setScore(200);
			resetGhost(prow, pcol, plast, pbool, pinkey,ppos);
			pinkey->setChar('G');
			pattack = false;
			pattacktime = 0;
			next = false;
		}
		else if (abstract[row][col] == 8 || abstract[beforerow][beforecol] == 8){
			if (ilast == 2){
				pacman->setScore(10);
			}
			pacman->setScore(200);
			resetGhost(irow, icol, ilast,ibool, inkey,ipos);
			inkey->setChar('G');
			iattack = false;
			iattacktime = 0;
			next = false;
		}
		else if (abstract[row][col] == 9 || abstract[beforerow][beforecol] == 9){
			if (blast == 2){
				pacman->setScore(10);
			}
			pacman->setScore(200);
			resetGhost(brow, bcol, blast, bbool, blinkey,bpos);
			blinkey->setChar('G');
			battack = false;
			battacktime = 0;
			next = false;
		}
		else if (abstract[row][col] == 6 || abstract[beforerow][beforecol] == 6){
			if (clast == 2){
				pacman->setScore(10);
			}
			pacman->setScore(200);
			resetGhost(crow, ccol, clast, cbool, clyde,cpos);
			clyde->setChar('G');
			cattack = false;
			cattacktime = 0;
			next = false;
		}

		//attack booleans check
		attackCheck(pattacktime, pattack, pinkey);
		attackCheck(iattacktime, iattack, inkey);
		attackCheck(battacktime, battack, blinkey);
		attackCheck(cattacktime, cattack, clyde);

		

		// reactions
		if (reset == true){
			resetGhost(prow, pcol, plast, pbool, pinkey,ppos);
			resetGhost(irow, icol, ilast, ibool, inkey,ipos);
			resetGhost(brow, bcol, blast, bbool, blinkey,bpos);
			resetGhost(crow, ccol, clast, cbool, clyde,cpos);
			reset = false;
			clock = 0;
		}
		

		//board[row][col] = pacman;
		abstract[row][col] = 1;

		// level check ...lives up doesnt work and changes after input plus leaves ghosts in hull still
		if (levelCheck()){
			level = true;
			pacman->setLives(1);
			pacman->setLevel();
			pacman->reset(row, col);
			startAbstract();
		}

		if (level){
			plast = 0;
			ilast = 0;
			blast = 0;
			clast = 0;
			pbool = false;
			ibool = false;
			cbool = false;
			bbool = false;
			
			level = false;
		}
		setBoard();
		input->pacDisplay(board,ROW,COL,pacman,abstract);
	
		
	}
	input->leaderboard(pacman->getScore());
	cleanUp();
	
}

void Game::startAbstract(){
	// row 0 and 30
	for (int col = 0; col < COL; col++){
		abstract[0][col] = 4;
		abstract[ROW - 1][col] = 4;
	}
	//row 1 and 20
	for (int col = 1; col < 13; col++){
		abstract[1][col] = 2;
		abstract[20][col] = 2;
	}
	for (int col = 15; col < COL - 1; col++){
		abstract[1][col] = 2;
		abstract[20][col] = 2;
	}
	abstract[1][0] = 4;
	abstract[20][0] = 4;
	abstract[1][COL - 1] = 4;
	abstract[20][COL - 1] = 4;
	for (int col = 13; col < 15; col++){
		abstract[1][col] = 4;
		abstract[20][col] = 4;
	}
	//rows 2,4,21,22
	abstract[2][0] = 4;
	abstract[4][0] = 4;
	abstract[21][0] = 4;
	abstract[22][0] = 4;
	abstract[2][1] = 2;
	abstract[4][1] = 2;
	abstract[21][1] = 2;
	abstract[22][1] = 2;
	for (int col = 2; col < 6; col++){
		abstract[2][col] = 4;
		abstract[4][col] = 4;
		abstract[21][col] = 4;
		abstract[22][col] = 4;
	}
	abstract[2][6] = 2;
	abstract[4][6] = 2;
	abstract[21][6] = 2;
	abstract[22][6] = 2;
	for (int col = 7; col < 12; col++){
		abstract[2][col] = 4;
		abstract[4][col] = 4;
		abstract[21][col] = 4;
		abstract[22][col] = 4;
	}
	abstract[2][12] = 2;
	abstract[4][12] = 2;
	abstract[21][12] = 2;
	abstract[22][12] = 2;
	for (int col = 13; col < 15; col++){
		abstract[2][col] = 4;
		abstract[4][col] = 4;
		abstract[21][col] = 4;
		abstract[22][col] = 4;
	}
	abstract[2][15] = 2;
	abstract[4][15] = 2;
	abstract[21][15] = 2;
	abstract[22][15] = 2;
	for (int col = 16; col < 21; col++){
		abstract[2][col] = 4;
		abstract[4][col] = 4;
		abstract[21][col] = 4;
		abstract[22][col] = 4;
	}
	abstract[2][21] = 2;
	abstract[4][21] = 2;
	abstract[21][21] = 2;
	abstract[22][21] = 2;
	for (int col = 22; col < 26; col++){
		abstract[2][col] = 4;
		abstract[4][col] = 4;
		abstract[21][col] = 4;
		abstract[22][col] = 4;
	}
	abstract[2][26] = 2;
	abstract[4][26] = 2;
	abstract[21][26] = 2;
	abstract[22][26] = 2;
	abstract[2][27] = 4;
	abstract[4][27] = 4;
	abstract[21][27] = 4;
	abstract[22][27] = 4;
	// row 3
	abstract[3][0] = 4;
	abstract[3][1] = 3;
	abstract[3][2] = 4;
	for (int col = 3; col < 5; col++){
		abstract[3][col] = 0;
	}
	abstract[3][5] = 4;
	abstract[3][6] = 2;
	abstract[3][7] = 4;
	for (int col = 8; col < 11; col++){
		abstract[3][col] = 0;
	}
	abstract[3][11] = 4;
	abstract[3][12] = 2;
	for (int col = 13; col < 15; col++){
		abstract[3][col] = 4;
	}
	abstract[3][15] = 2;
	abstract[3][16] = 4;
	for (int col = 17; col < 20; col++){
		abstract[3][col] = 0;
	}
	abstract[3][20] = 4;
	abstract[3][21] = 2;
	abstract[3][22] = 4;
	for (int col = 23; col < 25; col++){
		abstract[3][col] = 0;
	}
	abstract[3][25] = 4;
	abstract[3][26] = 3;
	abstract[3][27] = 4;
	//rows 5 and 29
	abstract[5][0] = 4;
	abstract[29][0] = 4;
	abstract[5][COL - 1] = 4;
	abstract[29][COL - 1] = 4;
	for (int col = 1; col < COL - 1; col++){
		abstract[5][col] = 2;
		abstract[29][col] = 2;
	}
	//rows 6,7
	abstract[6][0] = 4;
	abstract[7][0] = 4;
	abstract[6][1] = 2;
	abstract[7][1] = 2;
	for (int col = 2; col < 6; col++){
		abstract[6][col] = 4;
		abstract[7][col] = 4;
	}
	abstract[6][6] = 2;
	abstract[7][6] = 2;
	for (int col = 7; col < 9; col++){
		abstract[6][col] = 4;
		abstract[7][col] = 4;
	}
	abstract[6][9] = 2;
	abstract[7][9] = 2;
	for (int col = 10; col < 18; col++){
		abstract[6][col] = 4;
		abstract[7][col] = 4;
	}
	abstract[6][18] = 2;
	abstract[7][18] = 2;
	for (int col = 19; col < 21; col++){
		abstract[6][col] = 4;
		abstract[7][col] = 4;
	}
	abstract[6][21] = 2;
	abstract[7][21] = 2;
	for (int col = 22; col < 26; col++){
		abstract[6][col] = 4;
		abstract[7][col] = 4;
	}
	abstract[6][26] = 2;
	abstract[7][26] = 2;
	abstract[6][27] = 4;
	abstract[7][27] = 4;
	//rows 8,26
	abstract[8][0] = 4;
	abstract[26][0] = 4;
	abstract[8][COL - 1] = 4;
	abstract[26][COL - 1] = 4;
	for (int col = 1; col < 7; col++){
		abstract[8][col] = 2;
		abstract[26][col] = 2;
	}
	for (int col = 7; col < 9; col++){
		abstract[8][col] = 4;
		abstract[26][col] = 4;
	}
	for (int col = 9; col < 13; col++){
		abstract[8][col] = 2;
		abstract[26][col] = 2;
	}
	for (int col = 13; col < 15; col++){
		abstract[8][col] = 4;
		abstract[26][col] = 4;
	}
	for (int col = 15; col < 19; col++){
		abstract[8][col] = 2;
		abstract[26][col] = 2;
	}
	for (int col = 19; col < 21; col++){
		abstract[8][col] = 4;
		abstract[26][col] = 4;
	}
	for (int col = 21; col < COL - 1; col++){
		abstract[8][col] = 2;
		abstract[26][col] = 2;
	}
	//row 9
	for (int col = 0; col < 6; col++){
		abstract[9][col] = 4;
	}
	abstract[9][6] = 2;
	for (int col = 7; col < 12; col++){
		abstract[9][col] = 4;
	}
	abstract[9][12] = 0;
	for (int col = 13; col < 15; col++){
		abstract[9][col] = 4;
	}
	abstract[9][15] = 0;
	for (int col = 16; col < 21; col++){
		abstract[9][col] = 4;
	}
	abstract[9][21] = 2;
	for (int col = 22; col < COL; col++){
		abstract[9][col] = 4;
	}
	//row 10
	for (int col = 0; col < 5; col++){
		abstract[10][col] = 0;
	}
	abstract[10][5] = 4;
	abstract[10][6] = 2;
	for (int col = 7; col < 12; col++){
		abstract[10][col] = 4;
	}
	abstract[10][12] = 0;
	for (int col = 13; col < 15; col++){
		abstract[10][col] = 4;
	}
	abstract[10][15] = 0;
	for (int col = 16; col < 21; col++){
		abstract[10][col] = 4;
	}
	abstract[10][21] = 2;
	abstract[10][22] = 4;
	for (int col = 23; col < COL; col++){
		abstract[10][col] = 0;
	}
	//row 11
	for (int col = 0; col < 5; col++){
		abstract[11][col] = 0;
	}
	abstract[11][5] = 4;
	abstract[11][6] = 2;
	for (int col = 7; col < 9; col++){
		abstract[11][col] = 4;
	}
	for (int col = 9; col < 19; col++){
		abstract[11][col] = 0;
	}
	
	for (int col = 19; col < 21; col++){
		abstract[11][col] = 4;
	}
	abstract[11][21] = 2;
	abstract[11][22] = 4;
	for (int col = 23; col < COL; col++){
		abstract[11][col] = 0;
	}
	//rows 12,16,18
	for (int col = 0; col < 5; col++){
		abstract[12][col] = 0;
		abstract[16][col] = 0;
		abstract[18][col] = 0;
	}
	abstract[12][5] = 4;
	abstract[16][5] = 4;
	abstract[18][5] = 4;
	abstract[12][6] = 2;
	abstract[16][6] = 2;
	abstract[18][6] = 2;
	for (int col = 7; col < 9; col++){
		abstract[12][col] = 4;
		abstract[16][col] = 4;
		abstract[18][col] = 4;
	}
	abstract[12][9] = 0;
	abstract[16][9] = 0;
	abstract[18][9] = 0;
	for (int col = 10; col < 18; col++){
		abstract[12][col] = 4;
		abstract[16][col] = 4;
		abstract[18][col] = 4;
	}
	abstract[12][18] = 0;
	abstract[16][18] = 0;
	abstract[18][18] = 0;
	for (int col = 19; col < 21; col++){
		abstract[12][col] = 4;
		abstract[16][col] = 4;
		abstract[18][col] = 4;
	}
	abstract[12][21] = 2;
	abstract[16][21] = 2;
	abstract[18][21] = 2;
	abstract[12][22] = 4;
	abstract[16][22] = 4;
	abstract[18][22] = 4;
	for (int col = 23; col < COL; col++){
		abstract[12][col] = 0;
		abstract[16][col] = 0;
		abstract[18][col] = 0;
	}
	//row 13
	for (int col = 0; col < 6; col++){
		abstract[13][col] = 4;
	}
	abstract[13][6] = 2;
	for (int col = 7; col < 9; col++){
		abstract[13][col] = 4;
	}
	abstract[13][9] = 0;
	abstract[13][10] = 4;
	for (int col = 11; col < 13; col++){
		abstract[13][col] = 0;
	}
	abstract[13][13] = 10;
	abstract[13][14] = 11;
	abstract[13][15] = 12;
	abstract[13][16] = 13;
	
	
	abstract[13][17] = 4;
	abstract[13][18] = 0;
	for (int col = 19; col < 21; col++){
		abstract[13][col] = 4;
	}
	abstract[13][21] = 2;
	for (int col = 22; col < COL; col++){
		abstract[13][col] = 4;
	}
	//row 14
	for (int col = 0; col < 6; col++){
		abstract[14][col] = 0;
	}
	abstract[14][6] = 2;
	for (int col = 7; col < 10; col++){
		abstract[14][col] = 0;
	}
	abstract[14][10] = 4;
	for (int col = 11; col < 17; col++){
		abstract[14][col] = 0;
	}
	abstract[14][17] = 4;
	for (int col = 18; col < 21; col++){
		abstract[14][col] = 0;
	}
	abstract[14][21] = 2;
	for (int col = 22; col < COL; col++){
		abstract[14][col] = 0;
	}
	//row 15
	for (int col = 0; col < 6; col++){
		abstract[15][col] = 4;
	}
	abstract[15][6] = 2;
	for (int col = 7; col < 9; col++){
		abstract[15][col] = 4;
	}
	abstract[15][9] = 0;
	abstract[15][10] = 4;
	for (int col = 11; col < 17; col++){
		abstract[15][col] = 0;
	}

	abstract[15][17] = 4;
	abstract[15][18] = 0;
	for (int col = 19; col < 21; col++){
		abstract[15][col] = 4;
	}
	abstract[15][21] = 2;
	for (int col = 22; col < COL; col++){
		abstract[15][col] = 4;
	}
	//row 17
	for (int col = 0; col < 5; col++){
		abstract[17][col] = 0;
	}
	abstract[17][5] = 4;
	abstract[17][6] = 2;
	for (int col = 7; col < 9; col++){
		abstract[17][col] = 4;
	}
	for (int col = 9; col < 19; col++){
		abstract[17][col] = 0;
	}
	for (int col = 19; col < 21; col++){
		abstract[17][col] = 4;
	}
	abstract[17][21] = 2;
	abstract[17][22] = 4;
	for (int col = 23; col < COL; col++){
		abstract[17][col] = 0;
	}
	//row 19
	for (int col = 0; col < 6; col++){
		abstract[19][col] = 4;
	}
	abstract[19][6] = 2;
	for (int col = 7; col < 9; col++){
		abstract[19][col] = 4;
	}
	abstract[19][9] = 0;
	for (int col = 10; col < 18; col++){
		abstract[19][col] = 4;
	}
	abstract[19][18] = 0;
	for (int col = 19; col < 21; col++){
		abstract[19][col] = 4;
	}
	abstract[19][21] = 2;
	for (int col = 22; col < COL; col++){
		abstract[19][col] = 4;
	}
	//row 23
	abstract[23][0] = 4;
	abstract[23][1] = 3;
	for (int col = 2; col < 4; col++){
		abstract[23][col] = 2;
	}
	for (int col = 4; col < 6; col++){
		abstract[23][col] = 4;
	}
	for (int col = 6; col < 15; col++){
		abstract[23][col] = 2;
	}
	abstract[23][15] = 1;
	
	for (int col = 16; col < 22; col++){
		abstract[23][col] = 2;
	}
	for (int col = 22; col < 24; col++){
		abstract[23][col] = 4;
	}
	for (int col = 24; col < 26; col++){
		abstract[23][col] = 2;
	}
	abstract[23][26] = 3;
	abstract[23][COL - 1] = 4;
	//rows 24,25
	for (int col = 0; col < 3; col++){
		abstract[24][col] = 4;
		abstract[25][col] = 4;
	}
	abstract[24][3] = 2;
	abstract[25][3] = 2;
	for (int col = 4; col < 6; col++){
		abstract[24][col] = 4;
		abstract[25][col] = 4;
	}
	abstract[24][6] = 2;
	abstract[25][6] = 2;
	for (int col = 7; col < 9; col++){
		abstract[24][col] = 4;
		abstract[25][col] = 4;
	}
	abstract[24][9] = 2;
	abstract[25][9] = 2;
	for (int col = 10; col < 18; col++){
		abstract[24][col] = 4;
		abstract[25][col] = 4;
	}
	abstract[24][18] = 2;
	abstract[25][18] = 2;
	for (int col = 19; col < 21; col++){
		abstract[24][col] = 4;
		abstract[25][col] = 4;
	}
	abstract[24][21] = 2;
	abstract[25][21] = 2;
	for (int col = 22; col < 24; col++){
		abstract[24][col] = 4;
		abstract[25][col] = 4;
	}
	abstract[24][24] = 2;
	abstract[25][24] = 2;
	for (int col = 25; col < COL; col++){
		abstract[24][col] = 4;
		abstract[25][col] = 4;
	}
	//rows 27,28
	abstract[27][0] = 4;
	abstract[28][0] = 4;
	abstract[27][1] = 2;
	abstract[28][1] = 2;
	for (int col = 2; col < 12; col++){
		abstract[27][col] = 4;
		abstract[28][col] = 4;
	}
	abstract[27][12] = 2;
	abstract[28][12] = 2;
	for (int col = 13; col < 15; col++){
		abstract[27][col] = 4;
		abstract[28][col] = 4;
	}
	abstract[27][15] = 2;
	abstract[28][15] = 2;
	for (int col = 16; col < 26; col++){
		abstract[27][col] = 4;
		abstract[28][col] = 4;
	}
	abstract[27][26] = 2;
	abstract[28][26] = 2;
	abstract[27][COL - 1] = 4;
	abstract[28][COL - 1] = 4;
}

void Game::ghostMove(int& row, int& col, int& last, bool& go,int prow,int pcol,bool attack,int attacktime,bool next,int& AIlast){
	
	if ((go == false) && (next == true)){
		if (abstract[11][15] == 0){
			abstract[row][col] = last;
			row = 11;
			col = 15;
			go = true;
			last = abstract[row][col];
		}
	}
	else if (go == true){
		if (row == 14 && col == 0){
			if (abstract[14][1] == 0){
				abstract[row][col] = last;
				col = 1;;
				last = abstract[row][col];
			}
			else{
				abstract[row][col] = last;
				col = 0;
				last = abstract[row][col];
			}
		}
		else if (row == 14 && col == 27){
			if (abstract[14][26] == 0){
				abstract[row][col] = last;
				col--;
				last = abstract[row][col];
			}
			else{
				abstract[row][col] = last;
				col = col;
				last = abstract[row][col];
			}
		}
		else{
			// condition check to make sure AI only called if the ghost can move 
			if (abstract[row][col - 1] < 4 || abstract[row][col + 1] < 4 || abstract[row - 1][col] < 4 || abstract[row + 1][col] < 4){
				if (attack == false){
					abstract[row][col] = last;
					AI(row, col, last, prow, pcol, 1,AIlast);
					last = abstract[row][col];
				}
				else if (attack == true && (attacktime%2) == 0){
					abstract[row][col] = last;
					AI(row, col, last, prow, pcol, -1,AIlast);
					last = abstract[row][col];
				}	
			}
		}	
	}
	
}

void Game::AI(int& row, int& col, int& last,int prow ,int pcol,int direct,int& AIlast){
	bool loop = true;

	if (AIlast == 1){
		if (abstract[row + 1 * direct][col] < 4){
			row = row + (1 * direct);
			loop = false;
		}
	}
	else if (AIlast == 2){
		if (abstract[row][col + 1 * direct] < 4){
			col = col + (1 * direct);
			loop = false;
		}
	}
	else if (AIlast == 3){
		if (abstract[row - 1 * direct][col] < 4){
			row = row - (1 * direct);
			loop = false;
		}
	}
	else if (AIlast == 4){
		if (abstract[row][col - 1 * direct] < 4){
			col = col - (1 * direct);
			loop = false;
		}
	}
	else{

	}

	if (loop){
		if (prow == row){
			if (pcol > col){
				if (abstract[row][col + 1 * direct] < 4){
					col = col + (1 * direct);
					AIlast = 2;
				}
				else if (abstract[row + 1 * direct][col] < 4){
					row = row + (1 * direct);
					AIlast = 1;
				}
				else if (abstract[row - 1 * direct][col] < 4){
					row = row - (1 * direct);
					AIlast = 3;
				}
				else{

				}
			}
			else if (pcol < col){
				if (abstract[row][col - 1 * direct] < 4){
					col = col - (1 * direct);
					AIlast = 4;
				}
				else if (abstract[row - 1 * direct][col] < 4){
					row = row - (1 * direct);
					AIlast = 3;
				}
				else if (abstract[row + 1 * direct][col] < 4){
					row = row + (1 * direct);
					AIlast = 1;
				}
				else{

				}
			}
		}
		else if (pcol == col){
			if (prow > row){
				if (abstract[row + 1 * direct][col] < 4){
					row = row + (1 * direct);
					AIlast = 1;
				}
				else if (abstract[row][col - 1 * direct] < 4){
					col = col - (1 * direct);
					AIlast = 4;
				}
				else if (abstract[row][col + 1 * direct] < 4){
					col = col + (1 * direct);
					AIlast = 2;
				}
				else{

				}
			}
			else if (prow < row){
				if (abstract[row - 1 * direct][col] < 4){
					row = row - (1 * direct);
					AIlast = 3;
				}
				else if (abstract[row][col + 1 * direct] < 4){
					col = col + (1 * direct);
					AIlast = 2;
				}
				else if (abstract[row][col - 1 * direct] < 4){
					col = col - (1 * direct);
					AIlast = 4;
				}
				else{

				}
			}
		}
		else if (pcol > col && prow > row) {
			if (abstract[row + 1 * direct][col] < 4){
				row = row + (1 * direct);
				AIlast = 1;
			}
			else if (abstract[row][col + 1 * direct] < 4){
				col = col + (1 * direct);
				AIlast = 2;
			}
			else if (abstract[row][col - 1 * direct] < 4){
				col = col - (1 * direct);
				AIlast = 4;
			}
			else{

			}
		}
		else if (pcol > col && prow < row){
			if (abstract[row][col + 1 * direct] < 4){
				col = col + (1 * direct);
				AIlast = 2;
			}
			else if (abstract[row - 1 * direct][col] < 4){
				row = row - (1 * direct);
				AIlast = 3;
			}
			else if (abstract[row][col - 1 * direct] < 4){
				col = col - (1 * direct);
				AIlast = 4;
			}
			else{

			}
		}
		else if (pcol < col && prow > row) {
			if (abstract[row + 1 * direct][col] < 4){
				row = row + (1 * direct);
				AIlast = 1;
			}
			else if (abstract[row][col - 1 * direct] < 4){
				col = col - (1 * direct);
				AIlast = 4;
			}
			else if (abstract[row - 1 * direct][col] < 4){
				row = row - (1 * direct);
				AIlast = 3;
			}
			else{

			}
		}
		else if (pcol < col && prow < row){
			if (abstract[row - 1 * direct][col] < 4){
				row = row - (1 * direct);
				AIlast = 3;
			}
			else if (abstract[row][col - 1 * direct] < 4){
				col = col - (1 * direct);
				AIlast = 4;
			}
			else if (abstract[row][col + 1 * direct] < 4){
				col = col + (1 * direct);
				AIlast = 2;
			}
			else{

			}
		}
	}
}
//not using
void Game::check(int& row, int& col,bool& reset){
	if (abstract[row][col] == 5){
		pacman->reset(row, col);
		reset = true;
		cout << '\a' << endl;
	}
}

void Game::resetGhost(int& row, int& col, int& last,bool& next,Ghost*& ghost,int pos){
	abstract[row][col] = last;
	row = ghost->getRow();
	col = ghost->getCol();
	last = abstract[row][col];
	abstract[row][col] = pos;

	next = false;
}

void Game::attackCheck(int& time, bool& attack, Ghost*& ghost){
	if (attack == true){
		time = time + 1;

		if (time == 25){
			ghost->setChar('G');
			attack = false;
			time = 0;
		}
	}
}

Game* Game::getGame(){
	if (game == NULL){
		game = new Game;
		return game;
	}
}

Game* Game::game = NULL;

void Game::cleanUp(){
	delete pinkey;
	delete pacman;
	delete inkey;
	delete clyde;
	delete blinkey;
	delete input;
	delete brick;
	delete blank;
	delete largepill;
	delete smallpill;

	pinkey = NULL;
	inkey = NULL;
	blinkey = NULL;
	clyde = NULL;
	pacman = NULL;
	brick = NULL;
	smallpill = NULL;
	largepill = NULL;
	blank = NULL;
	input = NULL;
}

bool Game::levelCheck(){
	for (int i = 0; i < ROW; i++){
		for (int j = 0; j < COL; j++){
			if (abstract[i][j] == 2 || abstract[i][j] == 3){
				return false;
			}
		}
	}
	return true;
}

void Game::setBoard(){
	for (int row = 0; row < ROW; row++){
		for (int col = 0; col < COL; col++){
			if (abstract[row][col] == 0){
				board[row][col] = blank;
			}
			else if (abstract[row][col] == 1){
				board[row][col] = pacman;
			}
			else if (abstract[row][col] == 2){
				board[row][col] = smallpill;
			}
			else if (abstract[row][col] == 3){
				board[row][col] = largepill;
			}
			else if (abstract[row][col] == 4){
				board[row][col] = brick;
			}
			else if (abstract[row][col] == 6 || abstract[row][col] == 10){
				board[row][col] = clyde;
			}
			else if (abstract[row][col] == 7 || abstract[row][col] == 11){
				board[row][col] = pinkey;
			}
			else if (abstract[row][col] == 8 || abstract[row][col] == 12){
				board[row][col] = inkey;
			}
			else if (abstract[row][col] == 9 || abstract[row][col] == 13){
				board[row][col] = blinkey;
			}
		}
	}
}