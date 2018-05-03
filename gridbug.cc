#include "gridbug.h"

bool GridBug::_hostile = true;

GridBug::GridBug(Cell* location) : Character(location, 'X'){}

GridBug::~GridBug() {}

void GridBug::tick() {
	if (DoTick) {

		// All directions that a wee little grid bug can see
		int view[4] = {1, 3, 4, 6};

		// Look for the Player
		GameObject* victim = 0;
		for ( int i = 0 ; i < 4 ; ++i ) {
			if (_location->neighbours[view[i]]->display() == '@') {
				victim = _location->neighbours[view[i]]->_contents;
				break;
			}
		}

		// Attack if player found, move if not
		if (victim != 0 && _hostile) {
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
			for ( int i = 0 ; i < 4 ; ++i ) {
				if (_location->neighbours[view[i]]->ObjCanOcc) {				// If Object Can Occupy cell
					MoveOptions.push_back(_location->neighbours[view[i]]);		// Add to list
				}
			}

			// If no options, don't move
			if (MoveOptions.size() == 0) return;

			// Initiate move
			int gohere = prng(MoveOptions.size() - 1);		// Decrement options by 1 to account for 0th option.
			move(MoveOptions[gohere]);				// Make new Cell my _location
		}
		DoTick = false;
	}
}

void GridBug::attack(GameObject *attacker){
	// Print message if first attack on a grid bug
	if (!GridBug::_hostile) std::cout << "This is an act of war to every Grid Bug!" << std::endl;
  _hostile = true;
  Character::attack(attacker);
}

void GridBug::setHostile(bool b){
  _hostile = b;
}
