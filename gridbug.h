#ifndef GRIDBUG_H
#define GRIDBUG_H
#include "character.h"
#include "PRNG.h"
#include <cmath>
#include <iostream>

class GridBug : public Character {
  static bool _hostile; //global hostile setting for this monster
    public:

    	GridBug(Cell* location);
    	~GridBug();

	static void setHostile(bool b);
    void tick();
	void attack(GameObject * attacker);
};


#endif
