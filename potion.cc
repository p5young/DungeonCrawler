#include "potion.h"

Potion::Potion(Cell* location, char type) : GameObject(location, '!') {

	switch (type) {
		case '0':
			// restore health
			_value = 30;
			_health = 10000;
			break;
		case '1':
			// boost attack
			_value = 10;
			_health = 20000;
			break;
		case '2':
			// boost defence
			_value = 10;
			_health = 30000;
			break;
		case '3':
			// poison health
			_value = -15;
			_health = 10000;
			break;
		case '4':
			// wound attack
			_value = -10;
			_health = 20000;
			break;
		case '5':
			// wound defence
			_value = -5;
			_health = 30000;
			break;
	}

}

Potion::~Potion() {}

void Potion::use(GameObject* user) {
	switch (_health) {
		case 10000:
			user->ModHealth(_value);
			if (user->display() == '@') {
				if (_value > 0) {
					std::cout << "You chug the Restore Health potion." << std::endl;
				} else {
					std::cout << "You chug the Poison Health potion." << std::endl;
				}
			}
			break;
		case 20000:
			user->ModAttack(_value);
			if (user->display() == '@') {
				if (_value > 0) {
					std::cout << "You chug the Boost Attack potion." << std::endl;
				} else {
					std::cout << "You chug the Wound Attack potion." << std::endl;
				}
			}
			break;
		case 30000:
			user->ModDefence(_value);
			if (user->display() == '@') {
				if (_value > 0) {
					std::cout << "You chug the Boost Defence potion." << std::endl;
				} else {
					std::cout << "You chug the Wound Defence potion." << std::endl;
				}
			}
			break;
	}
	_health = 0;
}

int Potion::health() {
	return _health;
}
