#include "gameobject.h"

GameObject::GameObject() {}

// Constructor
GameObject::GameObject(Cell* location, char display) : _location(location) {
	_display = display;
	_location->ObjCanOcc = false;
	_location->PlayerCanOcc = false;
	DoTick = true;

	// Present player object as '@'
	switch (display) {
		case 'k':
		case 's':
		case 'w':
			_display = '@';
	}

	_location->AddObject(this);
}

GameObject::~GameObject() {}

void GameObject::SetLocation(Cell* location) {
	_location = location;
	_location->AddObject(this);
}

// getter
int GameObject::x() const {
	return _location->x();
}
// getter
int GameObject::y() const {
	return _location->y();
}
// getter
char GameObject::display() {
	return _display;
}
// getter
std::string GameObject::name() const {
	return "Error: Name called on object non character";
}
// getter
std::string GameObject::weapon() const {
	return "Error: weapon called on object non character";
}
// getter
int GameObject::maxhealth() {
	return 100;
}
// getter
int GameObject::health() {
	return 100;
}
// getter
int GameObject::attack() {
	return 100;
}
// getter
int GameObject::defence() {
	return 100;
}
// Modifies Object Health
void GameObject::ModHealth(int amount) {}
// Modifies Object Attack
void GameObject::ModAttack(int amount) {}
// Modified Object Defence
void GameObject::ModDefence(int amount) {}
// Tick will be overridden by character
void GameObject::tick() {}
// Attack this object
void GameObject::attack(GameObject* attacker) {}
// Use this object
void GameObject::use(GameObject* user) {}