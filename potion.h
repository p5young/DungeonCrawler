#ifndef POTION_H
#define POTION_H

#include "gameobject.h"

class Potion : public GameObject {
    int _value;
    int _health;

	public:
		Potion(Cell* location, char type);
		~Potion();

		void use(GameObject* user);
		int health();
};

#endif
