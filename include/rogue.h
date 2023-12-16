#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

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

  Position **doors;
  // Monster **monsters;
  // Item **items;
} Room;

typedef struct Player
{
  Position * position;
  int health;
  int attack;
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

int screenSetUp();

// level/map functions
Room **roomsSetUp();
char **saveLevelPositions();
Level *createLevel(int level);

// player functions
Player *playerSetUp();
Position *handleInput(int input, Player *user);
int checkPosition(Position *newPosition, Level *level);
int playerMove(Position *newPosition, Player *user, char **level);

// room functions
Room * createRoom(int x, int y, int height, int width);
int connectDoors(Position *doorOne, Position *doorTwo);
int drawRoom(Room *room);

// monster functions
int addMonsters(Level *level);
Monster * selectMonster(int level);
Monster * createMonster(char symbol, int health, int attack, int speed, int defense, int pathfinding);
int killMonster(Monster *monster);
int setStartingPosition(Monster * monster, Room * room);
int moveMonsters(Level * level);
int pathfindingSeek(Position * start, Position * destination);
int pathfindingRandom(Position * position);

int combat(Player *player, Monster *monster, int order);
Monster *getMonsterAt(Position *position, Monster **monsters);

