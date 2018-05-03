#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "cell.h"
#include <vector>
#include <iostream>             // for testing

// forward declaration because mutual reference
class Cell;

// GameObject  - Add other private members as necessary
class GameObject {
    char _display;          // My display character, which differs from my cell's display character
    friend class Game;
    friend class Cell;

    protected:
        bool DoTick;        // ensures tick() is only called on each object once per turn
        Cell* _location;    // the location of this object

    public:
        GameObject();
        GameObject(Cell* location, char display);	// constructor

        virtual ~GameObject();  // destructor

        void SetLocation(Cell* location);
        int x() const;  // getters
        int y() const;
        char display();

        // Give the Object's name, weapon, health, etc...
        virtual std::string name() const;
        virtual std::string weapon() const;
        virtual int maxhealth();
        virtual int health();
        virtual int attack();
        virtual int defence();

        // Adjust the Object's health, attack, or defence
        virtual void ModHealth(int amount);
        virtual void ModAttack(int amount);
        virtual void ModDefence(int amount);

        // Called after every turn
        virtual void tick();
        
        // Use these to interact with GameObject
        virtual void attack(GameObject* attacker);              // Attempt to deal damage to the GameObject

        virtual void use(GameObject* user);                     // Attempt to interact with the GameObject
};

#endif
