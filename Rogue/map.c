#include "rogue.h"

Tile** createMapTiles(void)
{
	Tile** tiles = calloc(MAP_HEIGHT, sizeof(Tile*)); 
	if (tiles == NULL)
	{
		perror("Error while allocation memory for tiles*");
		exit(1);
	}

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		tiles[y] = calloc(MAP_WIDTH, sizeof(Tile));
		if (tiles[y] == NULL)
		{
			perror("Error while allocating memory for tiles");
			exit(1);
		}

		for (int x = 0; x < MAP_WIDTH; x++)
		{
			tiles[y][x].ch = '#';	// char for walls
			tiles[y][x].color = COLOR_PAIR(WALL_COLOR); // color for walls
			tiles[y][x].walkable = false; // walls not walkable
		}
	}
	return tiles;
}

Position setupMap(void)
{
	int y, x, height, width, n_rooms;
	n_rooms = (rand() % 11) + 5;
	Room* rooms = calloc(n_rooms, sizeof(Room));
	if (rooms == NULL)
	{
		perror("Error allocating memory for rooms");
		exit(1);
	}
	Position start_pos;
	 

	for (int i = 0; i < n_rooms; i++)
	{
		y = (rand() % (MAP_HEIGHT - 10)) + 1;
		x = (rand() % (MAP_WIDTH - 20)) + 1;

		height = (rand() % 7) + 3;
		width = (rand() % 15) + 5;

		rooms[i] = createRoom(y, x, height, width);
		addRoomToMap(rooms[i]);

		if (i > 0)
		{
			connectRoomCenters(rooms[i - 1].center, rooms[i].center);
		}
	}

	start_pos.y = rooms[0].center.y;
	start_pos.x = rooms[0].center.x;

	free(rooms);

	return start_pos;
}

Position setupEnemyPosition(void)
{
	Position enemy_pos;

	// Ensure the enemy does not spawn on a wall
	do
	{
		enemy_pos.y = rand() % MAP_HEIGHT;
		enemy_pos.x = rand() % MAP_WIDTH;
	} while (!map[enemy_pos.y][enemy_pos.x].walkable);

	return enemy_pos;
}

Position setupKeyPosition(void)
{
	Position key_pos;
	do
	{
		key_pos.y = rand() % MAP_HEIGHT;
		key_pos.x = rand() % MAP_WIDTH;
	} while (!map[key_pos.y][key_pos.x].walkable);

	return key_pos;
}

Position setupDoorPosition(void)
{
	Position door_pos;
	int x_rad, y_rad;
	do
	{
		door_pos.y = rand() % MAP_HEIGHT;
		door_pos.x = rand() % MAP_WIDTH;
		x_rad = abs(door_pos.x - key->pos.x);
	} while (!map[door_pos.y][door_pos.x].walkable || x_rad < 10);

	return door_pos;
}

Position setupLifePosition(void)
{
	Position life_pos;
	do
	{
		life_pos.y = rand() % MAP_HEIGHT;
		life_pos.x = rand() % MAP_WIDTH;
	} while (!map[life_pos.y][life_pos.x].walkable);


	return life_pos;
}

void freeMap(void)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		free(map[y]); map[y] = NULL;
	}
	free(map); map = NULL;
}