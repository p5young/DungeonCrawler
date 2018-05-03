#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include <cmath>
#include "error.h"
#include <iostream>


class Player : public Character {
  void regAttack(int dir);
  void wizAttack(int dir);

 public:
  enum playerClass {Knight = 'k', Wizard = 'w', Samurai = 's'};

  Player(Cell * location, playerClass c);
  ~Player();

  void PlayerAttack(int dir);

  void resetStats();

  void attack(GameObject* attacker);
};
#endif
