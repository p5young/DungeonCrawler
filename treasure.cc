#include "treasure.h"

Treasure::Treasure(Cell* location, char type) : GameObject(location, '$') {
	
	// Assign values to use during collection
	// health is for identification by despawner and dragon
	if (type <= '6') {			// gold pile
		_value = 10;
		_health = 80;
		_takeable = true;
	} else if (type == '7') {	// dragon horde
		_value = 50;
		_health = 100;
		_takeable = false;
	}
}

Treasure::~Treasure() {}

void Treasure::use(GameObject* user) {
  if(! _takeable){//dragon has not been killed yet!
    std::cout << "It would be foolhardy to take the dragon's gold right now." << std::endl;
    return;
  }
	extern int GP;
	GP += _value;
	_health = 0;
	if (_value == 10) {
		std::cout << "You pick up the Gold Pile worth 10GP." << std::endl;
	} else {
		std::cout << "You successfully take the Dragon Hoard!" << std::endl;
	}
}

int Treasure::health() {
	return _health;
}

void Treasure::setTakeable(bool b){
  _takeable = b;
}
