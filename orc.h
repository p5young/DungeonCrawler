#ifndef ORC_H
#define ORC_H
#include "character.h"
#include "PRNG.h"
#include <iostream>

class Orc : public Character {
  public:
  
        static bool _hostile;
   
    	
    	Orc(Cell* location);
    	~Orc();

	virtual void attack(GameObject * attacker); //override
	static void setHostile(bool b);

    	void tick();
};



#endif
