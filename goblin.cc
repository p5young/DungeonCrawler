#include "goblin.h"

bool Goblin::_hostile = true; //hostile by default

Goblin::Goblin(Cell* location) : Character(location, 'g') {}

Goblin::~Goblin() {}

void Goblin::tick() {
	if (DoTick) {
		// Look for the Player
		GameObject* victim = _location->FindPlayer();

		if (victim != 0 && _hostile) {
			victim->attack(this);
		} else {
			// Get random number generator
			extern PRNG prng;

			// Create a vector of possible potions to drink
			std::vector<Cell*> DrinkOptions;

			// Collect drink options
			for (unsigned int i = 0 ; i < 8 ; ++i) {
				if (_location->neighbours[i]->display() == '!') 
				  DrinkOptions.push_back(_location->neighbours[i]);
			}

			// Drink em if you got em
			if (DrinkOptions.size() > 0) {
				int drinkhere = prng(DrinkOptions.size() - 1);
				DrinkOptions[drinkhere]->_contents->use(this);
				DoTick = false;
				return;													// Drinking success, return
			}

			// Check for stopwander cheat
      		extern bool stopwander;
      		if (stopwander) return;

			// Create a vector of possible places to move
			std::vector<Cell*> MoveOptions;

			// Collect move options
			for ( int i = 0 ; i < 8 ; ++i ) {							// 8 neighbours to every cell
				if (_location->neighbours[i]->ObjCanOcc) {				// If Object Can Occupy cell
					MoveOptions.push_back(_location->neighbours[i]);	// Add to list
				}
			}

			// If no options, don't move
			if (MoveOptions.size() == 0) return;

			// Initiate move
			int gohere = prng(MoveOptions.size() - 1);		// Decrement options by 1 to account for 0th option.
			move(MoveOptions[gohere]);
		}
		DoTick = false;
	}
}

void Goblin::attack(GameObject *attacker){
// Print message if first attack on a orc
	if (!Goblin::_hostile) std::cout << "This is an act of war to every Goblin!" << std::endl;
  _hostile = true;
  Character::attack(attacker);
}

void Goblin::setHostile(bool b){
  _hostile = b;
}
