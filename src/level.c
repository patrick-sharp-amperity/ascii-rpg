#include <rogue.h>

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

  return rooms;
}

char **saveLevelPositions()
{
  int x, y;
  char **positions;
  positions = malloc(sizeof(char *) *25);

  for (y = 0; y < 25; y++)
  {
    positions[y] = malloc(sizeof(char) * 100);
    for (x = 0; x < 100; x++)
    {
      positions[y][x] = (char) mvinch(y, x);
    }
  }

  return positions;
}
