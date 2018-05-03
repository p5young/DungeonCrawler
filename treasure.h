#ifndef TREASURE_H
#define TREASURE_H

#include "gameobject.h"

class Treasure : public GameObject {
    int _value;
    int _health;
    bool _takeable;

	public:
		Treasure(Cell* location, char type);
		~Treasure();

		void use(GameObject* user);
		int health();
		void setTakeable(bool b);

};

#endif
