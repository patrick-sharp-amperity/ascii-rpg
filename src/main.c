#include <rogue.h>

int main()
{
  int ch;
  Position *newPosition;
  Level *level;

  screenSetUp();

  level = createLevel(1);
  printGameHub(level);


  // main game loop
  while((ch = getch()) != 'q') 
  {
    printGameHub(level);
    newPosition = handleInput(ch, level->user);
    checkPosition(newPosition, level);
    moveMonsters(level);
    move(level->user->position->y, level->user->position->x);
  }

  endwin();

  return 0;
}


Room *createRoom(int grid)
{
  Room *newRoom;
  newRoom = malloc(sizeof(Room));

  switch (grid)
  {
    case 0:
      newRoom->position.x = 0;
      newRoom->position.y = 0;
      break;
    case 1:
      newRoom->position.x = 33;
      newRoom->position.y = 0;
      break;
    case 2:
      newRoom->position.x = 66;
      newRoom->position.y = 0;
      break;
    case 3:
      newRoom->position.x = 0;
      newRoom->position.y = 14;
      break;
    case 4:
      newRoom->position.x = 33;
      newRoom->position.y = 14;
      break;
    case 5:
      newRoom->position.x = 66;
      newRoom->position.y = 14;
      break;
  }


  newRoom->height = rand() %  6 + 4; // max 9
  newRoom->width  = rand() % 14 + 4; // max 17

  // offset

  newRoom->position.x += rand() % (29 - newRoom->width  + 1);
  newRoom->position.y += rand() % ( 9 - newRoom->height + 1);

  newRoom->doors = malloc(sizeof(Position *) * 4);

  // top door
  newRoom->doors[0] = malloc(sizeof(Position));
  newRoom->doors[0]->x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
  newRoom->doors[0]->y = newRoom->position.y;

  // left door
  newRoom->doors[1] = malloc(sizeof(Position));
  newRoom->doors[1]->x = newRoom->position.x;
  newRoom->doors[1]->y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;

  // bottom door
  newRoom->doors[2] = malloc(sizeof(Position));
  newRoom->doors[2]->x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
  newRoom->doors[2]->y = newRoom->position.y + newRoom->height - 1;

  // right door
  newRoom->doors[3] = malloc(sizeof(Position));
  newRoom->doors[3]->x = newRoom->position.x + newRoom->width - 1;
  newRoom->doors[3]->y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;

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
  mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
  mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
  mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
  mvprintw(room->doors[3]->y, room->doors[3]->x, "+");

  return 1;
}

int connectDoors(Position *doorOne, Position *doorTwo)
{
  Position temp;
  Position previous;

  int count = 0;

  temp.x = doorOne->x;
  temp.y = doorOne->y;

  previous = temp;

  while (1)
  {
    // left
    if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x - 1) == ' '))
    {
      previous.x = temp.x;
      temp.x = temp.x - 1;
    }
    // right
    else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x + 1) == ' '))
    {
      previous.x = temp.x;
      temp.x = temp.x + 1;
    }
    // down
    else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y + 1, temp.x) == ' '))
    {
      previous.y = temp.y;
      temp.y = temp.y + 1;
    }
    // up
    else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y - 1, temp.x) == ' '))
    {
      previous.y = temp.y;
      temp.y = temp.y - 1;
    }
    else
    {
      if (count == 0) 
      {
        temp = previous;
        count++;;
        continue;
      } 
      else 
      {
        return 0;
      }
    }

    mvprintw(temp.y, temp.x, "#");
  }
  return 1;
}

