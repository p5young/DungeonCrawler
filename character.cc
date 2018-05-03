#include "character.h"

Character::Character() {}

// Character Constructor
Character::Character(Cell* location, char display) : GameObject(location,display) {
	//std::cerr << "Character Constructor called" << std::endl;
	if (display == 'k') {
		_name = "Knight";
		_weapon = "Sword of Segfault";
		_health = _maxhealth = 100;
		_attack = 50;
		_defence = 50;
	} else if (display == 'w') {
		_name = "Wizard";
		_weapon = "Infinite Loop Laser";
		_health = _maxhealth = 60;
		_attack = 25;
		_defence = 0;
	} else if (display == 's') {
		_name = "Samurai";
		_weapon = "Memory Corruption Katana";
		_health = _maxhealth = 80;
		_attack = 50;
		_defence = 15;
	} else if (display == 'X') {
		_name = "Grid Bug";
		_health = _maxhealth = 50;
		_attack = 20;
		_defence = 10;
	} else if (display == 'g') {
		_name = "Goblin";
		_health = _maxhealth = 75;
		_attack = 30;
		_defence = 20;
	} else if (display == 'M') {
		_name = "Merchant";
		_health = _maxhealth = 100;
		_attack = 75;
		_defence = 5;
	} else if (display == 'O') {
		_name = "Orc";
		_health = _maxhealth = 120;
		_attack = 30;
		_defence = 30;
	} else if (display == 'D') {
		_name = "Dragon";
		_health = _maxhealth = 150;
		_attack = 50;
		_defence = 10;
	} else {
		std::cerr << "Error making character, attempted to build " << display << std::endl;
	}
	
}

Character::~Character() {}

std::string Character::name() const {
	return _name;
}

std::string Character::weapon() const {
	return _weapon;
}

int Character::maxhealth() {
	return _maxhealth;
}

int Character::health() {
	return _health;
}

int Character::attack() {
	return _attack;
}

int Character::defence() {
	return _defence;
}

void Character::ModHealth(int amount) {
	_health += amount;
	if (_health > _maxhealth) _health = _maxhealth;
	if (_health < 0) _health = 0;
}

void Character::ModAttack(int amount) {
	_attack += amount;
	if (_attack < 0) _attack = 0;
}

void Character::ModDefence(int amount) {
	_defence += amount;
	if (_defence > 100) _defence = 100;
	if (_defence < 0) _defence = 0;
}

// override from GameObject
void Character::tick() {}

// attack this Character
void Character::attack(GameObject* attacker) {

	int damage = attacker->attack();
	int dmg = ceil( damage * (100.0 - _defence) / 100.0);

	std::cout << "You attack the " << _name << " with your " << attacker->weapon();
	std::cout << " for " << dmg << " damage!" << std::endl;

	_health -= dmg;

	if ( _health < 0 ) _health = 0;
}

void Character::move(Cell* newlocation){
 
  newlocation->AddObject(this);                   // Add this object to new Cell                                                                       
  _location->AddObject(0);                                // Remove this Cell's _contents                                                      
  _location = newlocation;                       // Make new Cell my _location   

}

void Character::PlayerAttack(int dir) {}

void Character::resetStats(){}
