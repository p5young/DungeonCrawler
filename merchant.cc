#include "merchant.h"

bool Merchant::_hostile = false; //default false for Merchant;


Merchant::Merchant(Cell* location) : Character(location, 'M') {}

Merchant::~Merchant(){}

void Merchant::tick() {
  if (DoTick) {
    // Look for the Player                                                                                                                                               
    GameObject* victim = _location->FindPlayer();

    if (victim != 0 && Merchant::_hostile) {
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
      for ( int i = 0 ; i < 8 ; ++i ) {                                          // 8 neighbours to every cell                                        
	if (_location->neighbours[i]->ObjCanOcc) {                              // If Object Can Occupy cell                                                 
	  MoveOptions.push_back(_location->neighbours[i]);        // Add to list                                                                       
	}
      }

      // If no options, don't move                                                                                                                                 
      if (MoveOptions.size() == 0) return;

      // Initiate move                                                                                                                                             
      int gohere = prng(MoveOptions.size() - 1);              // Decrement options by 1 to account for 0th option.                                                 
      move(MoveOptions[gohere]);
    }
    DoTick = false;
  }
}

void Merchant::attack(GameObject * attacker){

  // Print message if first attack on a merchant
  if (!Merchant::_hostile) std::cout << "This is an act of war to every Merchant!" << std::endl;

  // Make merchants hostile
  setHostile(true);
  // Execute the attack
  Character::attack(attacker);
}

void Merchant::setHostile(bool b){
  _hostile = b;
}
