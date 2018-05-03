#ifndef CHARACTER_H
#define CHARACTER_H
#include "gameobject.h"
#include <iostream>
#include <cmath> // ceil

class Character : public GameObject {

    protected:
        std::string _name;
        std::string _weapon;
        int _maxhealth;
        int _health;
        int _attack;
        int _defence;

    public:
        Character();
        Character(Cell* location, char display);
        ~Character();

        std::string name() const;
        std::string weapon() const;
        int maxhealth();
        int health();
        int attack();
        int defence();
	
   
        void ModHealth(int amount);
        void ModAttack(int amount);
        void ModDefence(int amount);

        virtual void tick();    // override from GameObject
        virtual void attack(GameObject* attacker);
        virtual void move(Cell *location);
			  
        // Player Character attacks in 'dir' direction
        virtual void PlayerAttack(int dir);
        virtual void resetStats();
};

#endif
