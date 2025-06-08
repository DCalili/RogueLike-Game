#include "rogue.h"

#define UP 65
#define DOWN 66
#define RIGHT 67
#define LEFT 68


Entity* createPlayer(Position start_pos)
{
	Entity* newPlayer = calloc(1, sizeof(Entity));
	if (newPlayer == NULL)
	{
		perror("Failed to allocate memory for player");
		exit(1);
	}

	newPlayer->pos.y = start_pos.y;
	newPlayer->pos.x = start_pos.x;
	newPlayer->ch = '@';
	newPlayer->color = COLOR_PAIR(PLAYER_COLOR); // Set player color
	newPlayer->dead = false; // Player is alive at the start

	return newPlayer;
}

void handleInput(int input)
{
	Position newPos = { player->pos.y, player->pos.x };

	switch (input)
	{
		case KEY_UP:
			newPos.y--;
			break;
		case KEY_DOWN:
			newPos.y++;
			break;
		case KEY_LEFT:
			newPos.x--;
			break;
		case KEY_RIGHT:
			newPos.x++;
			break;
		default:
			break;
	}
	movePlayer(newPos);
}

void movePlayer(Position newPos)
{
	for (int i = 0; i < gameState->enemies_count; i++)
	{
		if (enemies[i]->pos.y == newPos.y && enemies[i]->pos.x == newPos.x && !player->invulnerable)
		{
			gameState->lives--;
			player->invulnerable = true;
			if (gameState->lives < 0)
			{
				player->dead = true; // Player dies if they collide with an enemy
				return;
			}
			
		}
		if (key->pos.y == newPos.y && key->pos.x == newPos.x)
		{
			key->taken = true;
			door->visible = true;
		}
		if ((door->pos.y == newPos.y && door->pos.x == newPos.x) && door->visible)
		{
			freeEverything();
			loadNewLevel();
		}
		if (life && (life->pos.y == newPos.y && life->pos.x == newPos.x) && !life->taken)
		{
			life->taken = true;
			gameState->lives++;
		}
	}
	if (map[newPos.y][newPos.x].walkable)
	{
		player->pos.y = newPos.y;
		player->pos.x = newPos.x;
	}
}