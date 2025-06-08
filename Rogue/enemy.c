#include "rogue.h"


Entity* createEnemy(Position start_pos)
{
	Entity* newEnemy = calloc(1, sizeof(Entity));
	if (newEnemy == NULL)
	{
		perror("Failed to allocate memory for enemy");
		exit(1);
	}
	newEnemy->pos.y = start_pos.y;
	newEnemy->pos.x = start_pos.x;
	newEnemy->ch = 'O';
	newEnemy->color = COLOR_PAIR(ENEMY_COLOR); // Set enemy color
	return newEnemy;
}

void handleEnemyInput(int input, Entity* enemy)
{
	Position newPos = { enemy->pos.y, enemy->pos.x };
	switch (input)
	{
		case 1:
			newPos.y--;
			break;
		case 2:
			newPos.y++;
			break;
		case 3:
			newPos.x--;
			break;
		case 4:
			newPos.x++;
			break;
		default:
			break;
	}
	moveEnemy(newPos, enemy);
}

void moveEnemy(Position newPos, Entity* enemy)
{
	if (newPos.y == player->pos.y && newPos.x == player->pos.x && !player->invulnerable)
	{
		gameState->lives--;
		
		if (gameState->lives < 0)
		{
			player->dead = true;
			return; // If the enemy moves to the player's position, the player dies
		}
		player->invulnerable = true;
		
	}
	if (map[newPos.y][newPos.x].walkable)
	{
		enemy->pos.y = newPos.y;
		enemy->pos.x = newPos.x;
	}
	

}