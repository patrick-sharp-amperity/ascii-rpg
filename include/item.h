#pragma once

#include "rogue.h"
#include "weapon.h"
//#include "potion.h"

typedef enum {WEAPON_TYPE, POTION_TYPE} ItemType;

typedef struct Item
{
  ItemType type;
  Position *position;

  union {
    Weapon *weapon;
    //Potion *potion;
  } item;

  char string[256];
} Item;

Item *createSword(int attack, int health);
