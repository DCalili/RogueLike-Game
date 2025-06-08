#include "rogue.h"

Key* createKey(Position start_pos)
{
	Key* new_key = calloc(1, sizeof(Key));
	if (new_key == NULL)
	{
		perror("Error allocating memory for key");
		exit(1);
	}

	new_key->pos.y = start_pos.y;
	new_key->pos.x = start_pos.x;
	new_key->ch = 'K';
	new_key->color = COLOR_PAIR(KEY_COLOR);
	new_key->taken = false;

	return new_key;
}