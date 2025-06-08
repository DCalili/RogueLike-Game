#include "rogue.h"

const int MAP_HEIGHT = 25; // Height of the game map
const int MAP_WIDTH = 100;  // Width of the game map

Entity* player; // Global player variable
Entity** enemies; // Global enemy variable]
Key* key;
Door* door;
Life* life;
Tile** map; // Game map represented as a 2D array of tiles
GameState* gameState;

int main(void)
{
	srand(time(NULL));
	cursesSetup(); // Set up the curses environment

	do
	{
		menu();
	} while (!gameState->end);
	

	return 0;
}