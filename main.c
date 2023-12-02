// gcc main.c -lncurses -o main && ./main

#include <ncurses.h>
#include <stdlib.h>

typedef struct Room
{
  int xPosition;
  int yPosition;
  int height;
  int width;
  // Monster **monsters;
  // Item **items;
} Room;

typedef struct Player
{
  int xPosition;
  int yPosition;
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
int drawRoom(Room *room);

int main()
{
  Player *user;
  int ch;
  screenSetUp();

  mapSetUp();

  user = playerSetUp();

  // main game loop
  while((ch = getch()) != 'q') 
  {
    handleInput(ch, user);

  }

  endwin();

  return 0;
}

int screenSetUp()
{
  initscr();
  printw("Hello, world!");
  noecho();
  refresh();

  return 1;
}

Room **mapSetUp()
{
  Room **rooms;
  rooms = malloc(sizeof(Room)*6);

  rooms[0] = createRoom(13, 13, 6, 8);
  drawRoom(rooms[0]);

  rooms[1] = createRoom(40, 2, 6, 8);
  drawRoom(rooms[1]);

  rooms[2] = createRoom(40, 10, 6, 8);
  drawRoom(rooms[2]);

  return rooms;
}

Room * createRoom(int x, int y, int height, int width)
{
  Room * newRoom;
  newRoom = malloc(sizeof(Room));
  newRoom->xPosition = x;
  newRoom->yPosition = y;
  newRoom->height = height;
  newRoom->width = width;

  return newRoom;
}

int drawRoom(Room *room)
{
  int x;
  int y;

  // draw top and bottom wall of room
  for (x = room->xPosition; x < room->xPosition + room->width; x++)
  {
    mvprintw(room->yPosition, x, "-");
    mvprintw(room->yPosition + room->height - 1, x, "-");
  }

  // draw side walls and floor
  for (y = room->yPosition + 1; y < room->yPosition + room->height - 1; y++)
  {
    // draw side walls for this y value
    mvprintw(y, room->xPosition, "|");
    mvprintw(y, room->xPosition + room->width - 1, "|");

    // draw the floor
    for (x = room->xPosition + 1; x < room->xPosition + room->width - 1; x++)
    {
      mvprintw(y, x, ".");
    }
  }

  return 1;
}

Player *playerSetUp()
{
  Player *newPlayer;
  newPlayer = malloc(sizeof(Player));

  newPlayer->xPosition = 14;
  newPlayer->yPosition = 14;
  newPlayer->health    = 20;

  playerMove(14, 14, newPlayer);

  return newPlayer;
}

int handleInput(int input, Player *user)
{
  int newY;
  int newX;

  switch (input)
  {
    case 'w':
    case 'W':
      newY = user->yPosition - 1;
      newX = user->xPosition;
      break;
    case 's':
    case 'S':
      newY = user->yPosition + 1;
      newX = user->xPosition;
      break;
    case 'a':
    case 'A':
      newY = user->yPosition;
      newX = user->xPosition - 1;
      break;
    case 'd':
    case 'D':
      newY = user->yPosition;
      newX = user->xPosition + 1;
      break;
    default:
      break;
  }

  checkPosition(newY, newX, user); 

  return 0;
}

int checkPosition(int newY, int newX, Player *user)
{
  int space;
  switch (mvinch(newY, newX))
  {
    case '.':
      playerMove(newY, newX, user);
      break;
    default:
      move(user->yPosition, user->xPosition);
      break;
  }
  return 0;
}

int playerMove(int y, int x, Player *user) {
  mvprintw(user->yPosition, user->xPosition, ".");

  user->yPosition = y;
  user->xPosition = x;

  mvprintw(user->yPosition, user->xPosition, "@");
  move(user->yPosition, user->xPosition);
  
  return 0;
}
