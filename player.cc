#include "player.h"

Player::Player(Cell *location, playerClass c) : Character(location, c) {}

Player::~Player(){}

void Player::PlayerAttack(int dir){
  if(_name == "Knight" || _name == "Samurai")
    regAttack(dir);
  else if (_name == "Wizard")
    wizAttack(dir);
}

void Player::regAttack(int dir){
  if (_location->neighbours[dir]->_contents != 0) {
    GameObject* victim = _location->neighbours[dir]->_contents;
    switch (victim->display()) {
    case 'X':                                                       // Fall through                                                                              
    case 'g':                                                       // Fall through                                                                              
    case 'M':                                                       // Fall through                                                                              
    case 'O':                                                       // Fall through                                                                              
    case 'D':                                                       // Fall through                                                                              
      victim->attack(this);
      break;
    default:
      throw error( "nothing there to attack" );
    }
  } else {
    throw error( "nothing there to attack" );
  }


}

// player is being attacked
void Player::attack(GameObject * attacker){
  int damage = attacker->attack();
  int dmg = ceil( damage * (100.0 - _defence) / 100.0);

  std::cout << "The evil " << attacker->name() << " strikes you for ";
  std::cout << dmg << " damage!" << std::endl;

  _health -= dmg;
  if (_health <= 0 ) {
    _health = 0;
  }
}

void Player::wizAttack(int dir){
  Cell * target = _location->neighbours[dir];
  while(true){

    if (target->_contents == 0){
      if(target->display() == '.'){
	target = target->neighbours[dir];
	continue;
      }
      else{
	throw error( "nothing there to attack");
      }
    }

    else{
      GameObject *victim = target->_contents;
      switch(target->display()){
         case 'X':
         case 'g':
         case 'M':
         case 'O':
         case 'D':
	   victim->attack(this);
	   return;
         default:
	   throw error ("nothing there to attack");
      }
    }
  }
}

void Player::resetStats(){
  if(_name == "Knight")
    _attack = _defence = 50;
  else if (_name == "Wizard"){
    _attack = 25;
    _defence = 0;
  }
  else if (_name == "Samurai"){
    _attack = 50;
    _defence = 15;
  }
}
