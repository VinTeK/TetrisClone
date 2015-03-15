#include <iostream>

#include "Game.hpp"

//#include <vld.h> /* DEBUG: MEMORY LEAK DETECTION */


int main()
{
	try {
		Game game;
		game.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
