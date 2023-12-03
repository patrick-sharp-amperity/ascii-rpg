#include <rogue.h>

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
    case '#':
    case '+':
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
