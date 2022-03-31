#include <iostream>
#include "Game.h"



int main() 
{
	//Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//Init game
	Game game;

	//Game Loop
	while (game.getWindowisOpen() && !game.getEndGame()) {
		
		//Update
		game.update();



		//Render
		game.render();

	}

	



	
	//end
	return 0;
}