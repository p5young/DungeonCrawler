#ifndef GOBLIN_H
#define GOBLIN_H
#include "character.h"
#include "PRNG.h"
#include <cmath>
#include <iostream>

class Goblin : public Character {
  static bool _hostile; // determines whether goblins are hostile to player
    public:

    	Goblin(Cell* location);
    	~Goblin();

	static void setHostile(bool b);
    	void tick();
	void attack(GameObject *attacker);
};

#endif
