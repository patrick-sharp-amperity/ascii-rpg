// gcc main.c -lncurses -o main && ./main

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

  Position doors[4];
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
int drawRoom(Room *room);

int main()
{
  Player *user;
  int ch;

  srand(time(NULL));

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
  newRoom->position.y = y;
  newRoom->position.x = x;
  newRoom->height = height;
  newRoom->width = width;

  // top door
  newRoom->doors[0].x = rand() % (width - 2) + x + 1;
  newRoom->doors[0].y = newRoom->position.y;

  // bottom door
  newRoom->doors[1].x = rand() % (width - 2) + x + 1;
  newRoom->doors[1].y = newRoom->position.y + newRoom->height - 1;

  // left door
  newRoom->doors[2].x = newRoom->position.x;
  newRoom->doors[2].y = rand() % (height - 2) + y + 1;

  // right door
  newRoom->doors[3].x = newRoom->position.x + newRoom->width - 1;
  newRoom->doors[3].y = rand() % (height - 2) + y + 1;

  return newRoom;
}

int drawRoom(Room *room)
{
  int x;
  int y;

  // draw top and bottom wall of room
  for (x = room->position.x; x < room->position.x + room->width; x++)
  {
    mvprintw(room->position.y, x, "-");
    mvprintw(room->position.y + room->height - 1, x, "-");
  }

  // draw side walls and floor
  for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++)
  {
    // draw side walls for this y value
    mvprintw(y, room->position.x, "|");
    mvprintw(y, room->position.x + room->width - 1, "|");

    // draw the floor
    for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
    {
      mvprintw(y, x, ".");
    }
  }

  // draw doors
  mvprintw(room->doors[0].y, room->doors[0].x, "+");
  mvprintw(room->doors[1].y, room->doors[1].x, "+");
  mvprintw(room->doors[2].y, room->doors[2].x, "+");
  mvprintw(room->doors[3].y, room->doors[3].x, "+");

  return 1;
}

Player *playerSetUp()
{
  Player *newPlayer;
  newPlayer = malloc(sizeof(Player));

  newPlayer->position.x = 14;
  newPlayer->position.y = 14;
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
      newY = user->position.y - 1;
      newX = user->position.x;
      break;
    case 's':
    case 'S':
      newY = user->position.y + 1;
      newX = user->position.x;
      break;
    case 'a':
    case 'A':
      newY = user->position.y;
      newX = user->position.x - 1;
      break;
    case 'd':
    case 'D':
      newY = user->position.y;
      newX = user->position.x + 1;
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
      move(user->position.y, user->position.x);
      break;
  }
  return 0;
}

int playerMove(int y, int x, Player *user) {
  mvprintw(user->position.y, user->position.x, ".");

  user->position.y = y;
  user->position.x = x;

  mvprintw(user->position.y, user->position.x, "@");
  move(user->position.y, user->position.x);
  
  return 0;
}
