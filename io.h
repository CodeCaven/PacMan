#ifndef IO_H
#define IO_H
#include "board.h"
#include "pacman.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>

using namespace std;

class IO{
private:
	string name;
public:
	void input(int&, int&);
	void title(string);
	void setName();
	void leaderboard(int);
	void scoreStore(string, int);
	void nameStore(string, string);
	void nameArray(vector<string>&, string);
	void scoreArray(vector<int>&, string, int);
	void selectionSort(int, vector<int>&, vector<string>&);
	void pacPlay();
	void pacDisplay(Board*[][28], int, int, Pacman*,int [][28]);
};




#endif