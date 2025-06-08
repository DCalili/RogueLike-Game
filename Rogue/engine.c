#include "rogue.h"

void cursesSetup(void)
{
	initscr();            // Initialize the window
	noecho();             // Don't echo input characters
	curs_set(0);          // Hide the cursor
	keypad(stdscr, TRUE); // Enable keypad input
	gameState = createGameState();
	if (has_colors())
	{
		start_color(); // Start color mode
		init_pair(PLAYER_COLOR, COLOR_BLUE, COLOR_BLACK); // Red color pair for player
		init_pair(WALL_COLOR, COLOR_GREEN, COLOR_BLACK); // Green color pair for walls
		init_pair(ENEMY_COLOR, COLOR_RED, COLOR_BLACK); // Yellow color pair for enemies
		init_pair(KEY_COLOR, COLOR_YELLOW, COLOR_BLACK);
		init_pair(DOOR_COLOR, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(PLAYER_INVULNERABLE_COLOR, COLOR_CYAN, COLOR_BLACK);
		init_pair(LIFE_COLOR, COLOR_WHITE, COLOR_BLACK);
	}
}

void gameLoop(void)
{
	timeout(100); // Set a timeout for getch() to avoid blocking
	int ch;

	
	drawEverything();

	while (1)
	{
		if (player->invulnerable)
		{
			player->color = COLOR_PAIR(PLAYER_INVULNERABLE_COLOR);
			gameState->invulnerable_turns--;

			if (gameState->invulnerable_turns == 0)
			{
				player->invulnerable = false;
				gameState->invulnerable_turns = 20;
				player->color = COLOR_PAIR(PLAYER_COLOR);
			}
		}
		
		ch = getch(); // Get user input
		if (ch == 'q' || player->dead)
			break; // Exit on 'q' or if player is dead

		gameState->tick++;

		handleInput(ch); // Handle input for player movement
		if (gameState->tick % 3 == 0)
		{
			for (int i = 0; i < gameState->enemies_count; i++)
			{
				int  ch2 = (rand() % 4) + 1; // Random input for enemy movement
				handleEnemyInput(ch2, enemies[i]);
			}
		}
		

		drawEverything();
	}
	if (player->dead)
	{
		saveScore();
	}
}
void loadNewLevel(void)
{
	int num;
	gameState->level++;
	gameState->enemies_count++;

	Position start_pos; // Starting position for the player
	Position enemy_pos; // Starting position for the enemy
	Position key_pos;
	Position door_pos;
	Position life_pos;



	map = createMapTiles();
	start_pos = setupMap();


	player = createPlayer(start_pos); // Create the player entity
	player->invulnerable = true;
	enemies = calloc(gameState->enemies_count, sizeof(Entity*)); // Allocate memory for enemies
	if (enemies == NULL)
	{
		perror("Error allocating memory for enemies");
		exit(1);
	}
	for (int i = 0; i < gameState->enemies_count; i++) // Create multiple enemies
	{
		enemy_pos = setupEnemyPosition();
		enemies[i] = createEnemy(enemy_pos); // Create the enemy entity
	}

	key_pos = setupKeyPosition();
	key = createKey(key_pos);

	door_pos = setupDoorPosition();
	door = createDoor(door_pos);

	num = (rand() % 5) + 1;
	if (num == 2)
	{
		life_pos = setupLifePosition();
		life = createLife(life_pos);
	}
	

}

void freeEverything(void)
{
	freeMap();
	free(player); player = NULL;
	free(key); key = NULL;
	free(door); door = NULL;
	if (life)
		free(life); life = NULL;
	for (int i = 0; i < gameState->enemies_count; i++)
	{
		free(enemies[i]); enemies[i] = NULL;
	}
	
}
void menu(void)
{
	clear();
	printw("-----Rogue Game!-----");
	printw("\n| 1. Play           |");
	printw("\n| 2. Rules          |");
	printw("\n| 3. Scores         |");
	printw("\n| 4. Exit           |");
	printw("\n---------------------\n");

	char ch = getch();
	char ch2;
	switch (ch)
	{
		case '1':
			resetGameState();
			loadNewLevel();
			gameLoop(); // Start the game loop
			freeEverything(); // Clean up and close the game
			break;
		case '2':

			do {
				clear();
				printw("--------------------------------Rules--------------------------------\n");
				printw("| You are the player '@'.                                           |\n");
				printw("| Your goal is to get the Key 'K'                                   |\n");
				printw("| and go to the Door 'H'                                            |\n");
				printw("| You must avoid the enemies 'o', otherwise you'll lost a life      |\n");
				printw("| You have 3 lifes and can get more when the '+' appears            |\n");
				printw("| Everytime you pass a level the number of enemies increase by 1    |\n");
				printw("| How far can you go?                                               |\n");
				printw("---------------------------------------------------------------------");

				printw("\n\npress q to return.");
				ch2 = getch();
			} while (ch2 != 'q');
			break;
		
		case '3':
			readScore();
			break;

		case '4':
			gameState->end = true;
			break;
	}
}

void saveScore(void)
{
	int ch;

	mvprintw(MAP_HEIGHT + 1, 0, "You died :( press a to accept your death.");
	do {
		timeout(-1); // Torna getch() bloqueante novamente
		ch = getch();
	} while (ch != 'a');
	refresh();
	char* name = (char*)malloc(20);
	if (name == NULL)
	{
		perror("Error allocating memory for name");
		exit(1);
	}
	mvprintw(MAP_HEIGHT + 2, 0, "Enter you name: ");
	echo();
	wgetnstr(stdscr, name, sizeof(name) - 1);
	noecho();
	FILE* file = fopen("scores.txt", "a");
	if (file == NULL)
	{
		perror("Error while opening the file.");
		exit(1);
	}
	fprintf(file, "Name: %s - Score: %d\n", name, gameState->level);
	fclose(file);
}

void readScore(void)
{
	char line[50];
	int line_count = 0;
	FILE* file = fopen("scores.txt", "r");
	if (file == NULL)
	{
		perror("Error while opening scores file");
		exit(1);
	}

	clear();
	while (fgets(line, sizeof(line), file))
	{
		mvprintw(line_count,1,"%s", line);
		line_count++;
	}

	fclose(file);
	char ch;
	do
	{
		mvprintw(line_count + 5, 1, "press q to return");
		ch = getch();
	} while (ch != 'q');
}


void closeGame(void)
{
	freeMap(); map = NULL;
	free(player); player = NULL; // Free the player entity
	free(key); key = NULL;
	free(door); door = NULL;
	if (life)
		free(life); life = NULL;
	for (int i = 0; i < gameState->enemies_count; i++)
	{
		if (enemies[i])
			free(enemies[i]); enemies[i] = NULL; // Free the enemy entity
	}
}