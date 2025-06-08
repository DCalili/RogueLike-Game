#include "rogue.h"

void drawMap(void)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			mvaddch(y, x, map[y][x].ch | map[y][x].color);
		}
	}
	printw("\nLevel: %d \nLives: %d", gameState->level, gameState->lives);
}

void drawEntity(Entity* entity)
{
	mvaddch(entity->pos.y, entity->pos.x, entity->ch | entity->color);
}

void drawKey(Key* key)
{
	if (!key->taken)
		mvaddch(key->pos.y, key->pos.x, key->ch | key->color);
	else
		return;
}

void drawDoor(Door* door)
{
	if (door->visible)
		mvaddch(door->pos.y, door->pos.x, door->ch | door->color);
	else
		return;
}

void drawLife(Life* life)
{
	if (life && !life->taken)
	{
		mvaddch(life->pos.y, life->pos.x, life->ch | life->color);
	}
}
void drawEverything(void)
{
	clear();
	drawMap();
	drawEntity(player);
	drawKey(key);
	drawDoor(door);
	if (life)
		drawLife(life);
	for (int i = 0; i < gameState->enemies_count; i++)
	{
		drawEntity(enemies[i]);
	}
}