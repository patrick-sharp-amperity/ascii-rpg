#include <rogue.h>
#include <utils.h>

Level *createLevel(int level)
{
  Level *newLevel;
  newLevel = malloc(sizeof(Level));

  newLevel->level = level; 
  newLevel->numberOfRooms = 3;
  newLevel->rooms = roomsSetUp();
  newLevel->tiles = saveLevelPositions();

  newLevel->user = playerSetUp();
  placePlayer(newLevel->rooms, newLevel->user);

  addMonsters(newLevel);

  return newLevel;
}

Room **roomsSetUp()
{
  Room **rooms;
  rooms = malloc(sizeof(Room)*6);

  for (int x = 0; x < 6; x++)
  {
    rooms[x] = createRoom(x);
    drawRoom(rooms[x]);
  }

  pathFind(rooms[0]->doors[3], rooms[1]->doors[1]);

  return rooms;
}

char **saveLevelPositions()
{
  int x, y;
  char **positions;
  positions = malloc(sizeof(char *) * MAX_HEIGHT);

  for (y = 0; y < MAX_HEIGHT; y++)
  {
    positions[y] = malloc(sizeof(char) * MAX_WIDTH);
    for (x = 0; x < MAX_WIDTH; x++)
    {
      positions[y][x] = (char) mvinch(y, x);
    }
  }

  return positions;
}
