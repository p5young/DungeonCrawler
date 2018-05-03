#ifndef DRAGON_H
#define DRAGON_H
#include "treasure.h"
#include "character.h"
#include "PRNG.h"
#include <iostream>

class Dragon : public Character {
 public:

  static bool _hostile; // determine whether this time of enemy attacks player
  Treasure * _treasure;

  Dragon(Cell* location, Treasure * treasure);
  ~Dragon();

  virtual void attack(GameObject * attacker); //override                            
  static void setHostile(bool b); 

  void tick();
};

#endif
