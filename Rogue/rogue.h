#ifndef  ROGUE_H // Include guard for Rogue game header file
#define ROGUE_H // Rogue game header file

#define PLAYER_COLOR 1
#define WALL_COLOR 2
#define ENEMY_COLOR 3
#define KEY_COLOR 4
#define DOOR_COLOR 5
#define PLAYER_INVULNERABLE_COLOR 6
#define LIFE_COLOR 7



#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	int level;
	int lives;
	int enemies_count;
	int invulnerable_turns;
	int tick;
	bool end;

} GameState;

typedef struct 
{
	int y;          // Y coordinate
	int x;          // X coordinate
} Position;

typedef struct
{
	char ch; // Character representation of the position
	int color; // Color attribute for the tile
	bool walkable; // Indicates if the tile is walkable
} Tile ;

typedef struct
{
	int height;
	int width;
	Position pos;
	Position center;
} Room;

typedef struct
{
	Position pos; 	// Position of the item
	char ch; 	// Character representation of the item
	int color; // Color attribute for the item
	bool dead; // Indicates if the entity is dead
	bool invulnerable;
} Entity;

typedef struct
{
	Position pos;
	char ch;
	int color;
	bool taken;
} Key;

typedef struct
{
	Position pos;
	char ch;
	int color;
	bool visible;
} Door;

typedef struct
{
	Position pos;
	char ch;
	int color;
	bool taken;
} Life;

// gameState.c functions
GameState* createGameState(void);
void resetGameState(void);
// player.c functions
Entity* createPlayer(Position start_pos);
void handleInput(int input);
void movePlayer(Position newPos);

// enemy.c functions
Entity* createEnemy(Position start_pos);
void handleEnemyInput(int input, Entity* enemy);
void moveEnemy(Position newPos, Entity* enemy);

// key.c functions
Key* createKey(Position start_pos);

// door.c funtions
Door* createDoor(Position start_pos);

// life.c functions
Life* createLife(Position start_pos);

// room.c functions
Room createRoom(int y, int x, int height, int width);
void addRoomToMap(Room room);
void connectRoomCenters(Position centerOne, Position centerTwo);

// engine.c functions
void cursesSetup(void);
void freeEverything(void);
void loadNewLevel(void);
void gameLoop(void);
void closeGame(void);
void saveScore(void);
void readScore(void);
void menu(void);

// map.c functions
Tile** createMapTiles(void);
Position setupMap(void);
Position setupEnemyPosition(void);
Position setupKeyPosition(void);
Position setupDoorPosition(void);
Position setupLifePosition(void);
void freeMap(void);

// draw.c functions
void drawMap(void);
void drawEntity(Entity* entity);
void drawKey(Key* key);
void drawDoor(Door* door);
void drawLife(Life* life);
void drawEverything(void);
// externs
extern const int MAP_HEIGHT; // Height of the game map
extern const int MAP_WIDTH;  // Width of the game map
extern Entity* player; // Global player variable
extern Entity** enemies; // Global enemy variable
extern Key* key;
extern Door* door;
extern Life* life;
extern Tile** map; // Game map represented as a 2D array of tiles
extern GameState* gameState;

#endif //  ROGUE_H
