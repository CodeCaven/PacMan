#include "game.h"

int main(){
	Game* game = NULL;
	game = Game::getGame();
	if (game != NULL){
		game->gameLogic();
		delete game;
		game = NULL;
	}
	

	system("pause");
	return 0;
}