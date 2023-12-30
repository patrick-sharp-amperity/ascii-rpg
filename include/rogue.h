#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

// Struct definitions

typedef struct Level
{
  char **tiles;
  int level;
  int numberOfRooms;
  struct Room **rooms;
  int numberOfMonsters;
  struct Monster **monsters;
  struct Player *user;
} Level;

typedef struct Position
{
  int x;
  int y;
} Position;

typedef struct Room
{
  Position position;
  int height;
  int width;

  int numberOfDoors;
  struct Door ** doors;
  // Monster **monsters;
  // Item **items;
} Room;

typedef struct Door
{
  Position position;
  int connected;
} Door;

typedef struct Player
{
  Position * position;
  int health;
  int attack;
  int gold;
  int maxHealth;
  int exp;
} Player;

typedef struct Monster
{
  char string[2];
  char symbol;
  int health;
  int attack;
  int speed;
  int defense;
  int pathfinding;
  int alive;
  Position * position;
} Monster;


// Global variables
int MAX_HEIGHT; 
int MAX_WIDTH; 

// screen functions
int screenSetUp();
int printGameHub(Level *level);

// level/map functions
Room **roomsSetUp();
char **saveLevelPositions();
Level *createLevel(int level);

// player functions
Player *playerSetUp();
int placePlayer(Room **rooms, Player *user);
Position *handleInput(int input, Player *user);
int checkPosition(Position *newPosition, Level *level);
int playerMove(Position *newPosition, Player *user, char **level);

// room functions
Room *createRoom(int grid, int numberOfDoors);
void connectDoors(Level *level);
int drawRoom(Room *room);

// monster functions
int addMonsters(Level *level);
Monster *selectMonster(int level);
Monster *createMonster(char symbol, int health, int attack, int speed, int defense, int pathfinding);
int killMonster(Monster *monster);
int setStartingPosition(Monster *monster, Room *room);
int moveMonsters(Level *level);
int pathfindingSeek(Position *start, Position *destination);
int pathfindingRandom(Position *position);

int combat(Player *player, Monster *monster, int order);
Monster *getMonsterAt(Position *position, Monster **monsters);

