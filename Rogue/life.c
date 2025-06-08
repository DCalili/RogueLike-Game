#include "rogue.h"

Life* createLife(Position new_pos)
{
	Life* new_life = calloc(1, sizeof(Life));
	if (new_life == NULL)
	{
		perror("Error while allocating memory for life");
		exit(1);
	}

	new_life->pos.y = new_pos.y;
	new_life->pos.x = new_pos.x;
	new_life->ch = '+';
	new_life->taken = false;
	new_life->color = COLOR_PAIR(LIFE_COLOR);

	return new_life;
}