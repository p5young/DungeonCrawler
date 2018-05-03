#ifndef MERC_H
#define MERC_H

#include "character.h"
#include "PRNG.h"
#include <iostream>

class Merchant : public Character {
 public:
  static bool _hostile;
  
  
  Merchant(Cell* location);
  ~Merchant();
  
  virtual void attack(GameObject * attacker); //override
  static void setHostile(bool b);

  void tick();
};


#endif
