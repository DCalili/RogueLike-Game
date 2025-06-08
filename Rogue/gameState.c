#include "rogue.h"

GameState* createGameState(void)
{
	GameState* new_gameState = calloc(1, sizeof(GameState));
	if (new_gameState == NULL)
	{
		perror("Error allocating memory for gameState");
		exit(1);
	}

	new_gameState->level = 0;
	new_gameState->enemies_count = 0;
	new_gameState->lives = 3;
	new_gameState->invulnerable_turns = 20;
	new_gameState->end = false;

	return new_gameState;
}

void resetGameState(void)
{
	gameState->enemies_count = 0;
	gameState->level = 0;
	gameState->lives = 3;
	gameState->invulnerable_turns = 20;
	gameState->end = false;
}