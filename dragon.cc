#include "dragon.h"

bool Dragon::_hostile = true;


Dragon::Dragon(Cell * location, Treasure * treasure) : Character(location, 'D'), _treasure(treasure) {
} 

Dragon::~Dragon(){}

/* called each turn of the game; dragon attacks player if hostile and nearby */
void Dragon::tick() {
  if (DoTick) {
    // Look for the Player                                                                                                                                               
    GameObject* victim = _location->FindPlayer();

    if (victim != 0 && Dragon::_hostile)
      victim->attack(this);

    DoTick = false;
  }
}


/* attack target */
void Dragon::attack(GameObject *attacker){
  // Print message if first attack on a orc
  if (!Dragon::_hostile) std::cout << "This is an act of war to every Dragon!" << std::endl;
  setHostile(true);
  Character::attack(attacker);
  if(_health <= 0 && _treasure)
    _treasure->setTakeable(true); // allow the treasure to be taken
}

void Dragon::setHostile(bool b){
  _hostile = b;
}
