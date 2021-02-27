#include "io.h"

void IO::input(int& row, int& col){
	char temp;
	int frow = 0;
	int fcol = 0;

	temp = 'b';

	while (temp != 'a' && temp != 'w' && temp != 's' && temp != 'd'){
		temp = cin.get();
		cin.sync();
	}
	frow = row;
	fcol = col;

	if (temp == 'a'){
		if (frow == 14 && fcol == 0){
			fcol = 27;
		}
		else{
			fcol--;
		}
	}
	else if (temp == 'd'){
		if (frow == 14 && fcol == 27){
			fcol = 0;
		}
		else{
			fcol++;
		}
	}
	else if (temp == 'w'){
		frow--;
	}
	else if (temp == 's'){
		frow++;
	}
	row = frow;
	col = fcol;
}
// passing a multidimensional array by pointer
void IO::pacDisplay(Board* board[][28], int ROW, int COL, Pacman* pacman,int ab[][28]){
	for (int row = 0; row < ROW; row++){
		for (int col = 0; col < COL; col++){
			cout << board[row][col]->getChar();
				
		}
		cout << endl;
	}
	cout << ' ' << "Score: " << pacman->getScore() << " Level: "<< pacman->getLevel() << " Lives: " << pacman->getLives() << endl;
}

void IO::title(string title){
	cout << "***  WELCOME TO " << title << "   ***" << endl << endl;
}

void IO::setName(){
	cout << "Please enter your name " << endl << endl;
	cin >> name;
}

void IO::pacPlay(){
	cout << "Press W for Up, Press S for Down, Press A for Left, Press D for Right" << endl;
	this_thread::sleep_for(chrono::seconds(3));
}

void IO::leaderboard(int score){
	vector<string> nameVec;
	vector<int> scoreVec;

	string str1 = "score.txt";
	string str2 = "name.txt";
	int size;
	// Store the name and score to output files

	scoreStore(str1, score);
	nameStore(str2, name);

	// Read the scores and names into vectors for sorting and displaying

	nameArray(nameVec, str2);
	size = nameVec.size();
	scoreArray(scoreVec, str1, size);

	// Call selection sort function

	selectionSort(size, scoreVec, nameVec);

	// Display the Leaderboard 

	cout << "*** THE LEADERBOARD ***\n";

	for (int j = 0; j < size; j++){
		cout << scoreVec[j] << '\t' << nameVec[j] << '\n';
	}


}

void IO::scoreStore(string file, int total){
	ofstream hiscore;
	hiscore.open(file, ios::app);
	if (hiscore.is_open()){
		hiscore << total << '\n';
		hiscore.close();
	}
	else{
		cout << "File couldn't be opened\n";
	}
}

void IO::nameStore(string file, string title){
	ofstream hiscore;
	hiscore.open(file, ios::app);
	if (hiscore.is_open()){
		hiscore << title << '\n';
		hiscore.close();
	}
	else{
		cout << "File couldn't be opened\n";
	}
}

void IO::nameArray(vector<string>& name, string title){
	ifstream quizfile;
	string temp;
	quizfile.open(title);
	if (quizfile.is_open()){
		while (getline(quizfile, temp)){
			name.push_back(temp);
		}
		quizfile.close();
	}
	else{
		cout << "File couldn't be opened\n";
	}
}

void IO::scoreArray(vector<int>& score, string file, int loop){
	
	ifstream quizfile;
	int temp;
	quizfile.open(file);
	if (quizfile.is_open()){
		for (int i = 0; i < loop; i++){
			quizfile >> temp;
			score.push_back(temp);
		}
		quizfile.close();
	}
	else{
		cout << "File couldn't be opened\n";
	}
}

void IO::selectionSort(int a, vector<int>& hi, vector<string>& name){

	int index = 0;
	int max;
	int maxindex;
	int j;
	int itemp;
	string stemp;
	int k = 0;

	k = 0;
	while (k < a){
		max = hi[index];
		maxindex = index;
		j = 1 + index;

		while (j < a){
			if (max < hi[j]){
				max = hi[j];
				maxindex = j;
			}
			j++;
		}
		itemp = hi[maxindex];
		stemp = name[maxindex];
		hi[maxindex] = hi[index];
		name[maxindex] = name[index];
		hi[index] = itemp;
		name[index] = stemp;
		k++;
		index++;

	}
}