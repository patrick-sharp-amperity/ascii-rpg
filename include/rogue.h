#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

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
  Position position;
  int health;
} Player;

int screenSetUp();

// level/map functions
Room **mapSetUp();
char **saveLevelPositions();

// player functions
Player *playerSetUp();
Position *handleInput(int input, Player *user);
int checkPosition(Position *newPosition, Player *user, char **level);
int playerMove(Position *newPosition, Player *user, char **level);

// room functions
Room * createRoom(int x, int y, int height, int width);
int connectDoors(Position *doorOne, Position *doorTwo);
int drawRoom(Room *room);
