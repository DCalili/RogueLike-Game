#include "rogue.h"

Door* createDoor(Position new_pos)
{
	Door* new_door = calloc(1, sizeof(Door));
	if (new_door == NULL)
	{
		perror("Error allocating memory for door");
		exit(1);
	}

	new_door->pos.y = new_pos.y;
	new_door->pos.x = new_pos.x;
	new_door->ch = 'H';
	new_door->color = COLOR_PAIR(DOOR_COLOR);
	new_door->visible = false;

	return new_door;
}