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
Room **mapSetUp();
Player *playerSetUp();
int handleInput(int input, Player *user);
int playerMove(int y, int x, Player *user);
int checkPosition(int newY, int newX, Player *user);

// room functions
Room * createRoom(int x, int y, int height, int width);
int connectDoors(Position *doorOne, Position *doorTwo);
int drawRoom(Room *room);
