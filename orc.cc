#include "orc.h"

bool Orc::_hostile = true;


Orc::Orc(Cell* location) : Character(location, 'O') {
}

Orc::~Orc() {}

void Orc::tick() {
	if (DoTick) {
		// Look for the Player
		GameObject* victim = _location->FindPlayer();

		if (victim != 0 && Orc::_hostile) {
			victim->attack(this);
		} else {
			// Check for stopwander cheat
      		extern bool stopwander;
      		if (stopwander) return;

			// Get random number generator
			extern PRNG prng;

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

void Orc::attack(GameObject *attacker){
	// Print message if first attack on a orc
	if (!Orc::_hostile) std::cout << "This is an act of war to every Orc!" << std::endl;
  setHostile(true);
  Character::attack(attacker);
}

void Orc::setHostile(bool b){
  _hostile = b;
}
