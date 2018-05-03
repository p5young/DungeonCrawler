
#ifndef __GAME_H__
#define __GAME_H__
#include "cell.h"
#include "gameobject.h"
#include "character.h"
#include "player.h"
#include "orc.h"
#include "gridbug.h"
#include "goblin.h"
#include "treasure.h"
#include "potion.h"
#include "dragon.h"
#include "merchant.h"
#include "PRNG.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
using std::endl;
using std::cout;
using std::cerr;
using std::istream;
using std::setw;
extern int HEIGHT;
extern int WIDTH;
extern int GP;
extern istream* board;
extern bool spawns;
extern bool stopdeath;
extern PRNG prng;


class Game {
	Cell** grid;						// The actual grid.
	Character* player;					// The Player Character
	int Floor;							// Floor number
	int turns;							// Number of turns taken
	std::vector<GameObject*> objects;	// Vector to store GameObjects

	// Populates the game board
	// If this is not the first floor, make classtype = "Remove Potions"
	void NewFloor(std::string classtype);

	// calls tick on every cell in the grid, left-to-right, top-to-bottom
	void tick();

public:
	Game(std::string& classtype);
	~Game();

	void move(int dir);			// command to move
	void use(int dir);			// command to use
	void attack(int dir);		// command to attack

	void print();				// print theDisplay

	bool Tick;					// Flag for print() so cheats and new floors don't tick monsters
};

#endif
