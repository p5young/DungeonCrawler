#include "game.h"


// constructor
Game::Game(std::string &classtype) : grid() {

	// Number of turns taken and current floor
	turns = 1;
	Floor = 1;

	// Initialize player pointer to NULL
	player = 0;

	// Initialize grid = matrix of Cells
	grid = new Cell*[HEIGHT];
	for (int r = 0 ; r < HEIGHT ; ++r) {
		grid[r] = new Cell[WIDTH];
	}

	// Construct new floor
	NewFloor(classtype);

}  // constructor

// destructor
Game::~Game() {
	// Delete vector of GameObjects
	for (unsigned int i = 0 ; i < objects.size() ; ++i) {
		delete objects[i];
	}

	// Delete the player
	delete player;

	// Delete the grid of Cells
	for (int i = 0 ; i < HEIGHT ; ++i) {
		delete [] grid[i];
	}
	delete [] grid;

}  // destructor



// returns a vector of length 3
// returns r, c, room#
// where r, c == row, column
// room# is in the range (1,5)
// if notroom is specified (range 1,5), then this will return coordinates in a different room
std::vector<int> Game::Spawner(int notroom) {
	// return value
	std::vector<int> retval(3);

	// random number determining spawn
	int randval;
	if (notroom == 0) {
		randval = prng(604);	// 604 is the number of available locations on the map
	} else if (notroom == 1) {
		randval = prng(500) + 104;
	} else if (notroom == 2) {
		randval = prng(403);
		if (randval > 103) randval += 201;
	} else if (notroom == 3) {
		randval = prng(568);
		if (randval > 304) randval += 36;
	} else if (notroom == 4) {
		randval = prng(457);
		if (randval > 340) randval += 147;
	} else if (notroom == 5) {
		randval = prng(487);
	} else {
		cout << "ERROR: Spawner(notroom) called with invalid value" << endl;
	}

	// first room
	if (randval <= 103)
	{
		retval[0] = 3 + (randval / 26);	// row
		retval[1] = 3 + (randval % 26);	// col
		retval[2] = 1;					// room #
	}
	// second room
	else if (randval <= 304)
	{
		randval -= 104;	// make randval in the range (0, 200) because there's 201 spots in room 2
		if (randval <= 45) {
			retval[0] = 3 + (randval / 23);
			retval[1] = 39 + (randval % 23);
		} else if (randval <= 76) {
			randval -= 46;	// randval now in the range (0,30)
			retval[0] = 5;
			retval[1] = 39 + randval;
		} else if (randval <= 110) {
			randval -= 77;	// randval now in the range (0, 33)
			retval[0] = 6;
			retval[1] = 39 + randval;
		} else {
			randval -= 111;	// randval now in the range (0, 89)
			retval[0] = 7 + (randval / 15);
			retval[1] = 61 + (randval % 15);
		}
		retval[2] = 2;	// room #
	}
	// third room
	else if (randval <= 340)
	{
		randval -= 305;	// now in range (0, 35)
		retval[0] = 10 + (randval / 12);
		retval[1] = 38 + (randval % 12);
		retval[2] = 3;
	}
	// fourth room
	else if (randval <= 487)
	{
		randval -= 341;	// now in range (0, 146)
		retval[0] = 15 + (randval / 21);
		retval[1] = 5 + (randval % 21);
		retval[2] = 4;
	}
	// fifth room
	else if (randval <= 604)
	{
		randval -= 488;	// now in range (0, 116)
		if (randval <= 32) {
			retval[0] = 16 + (randval / 11);
			retval[1] = 65 + (randval % 11);
		} else {
			randval -= 32;	// now in range (0, 84)
			retval[0] = 19 + (randval / 39);
			retval[1] = 37 + (randval % 39);
		}
		retval[2] = 5;
	}

	return retval;
}


// Initialize a new floor; all consumable and monsters are deleted and randomly generated; player is create if it is start of game
void Game::NewFloor(std::string classtype) {
	// Tick is used in print() to ensure the monsters don't move the first time each floor is printed
	Tick = false;

	// delete vector of GameObjects
	for (unsigned int i = 0 ; i < objects.size(); ++i) {
		delete objects[i];
	}
	objects.erase(objects.begin(), objects.end());

	// Create temporary vectors to store pointers to Dragons and Hordes for later association
	std::vector<GameObject*> Dragons;
	std::vector<Treasure*> DragonHordes;

	// Fill the floor
	for (int r = 0 ; r < HEIGHT ; ++r) {
		for (int c = 0 ; c < WIDTH ; ++c) {
			char displaychar = board->get();	// read in from board
			grid[r][c] = Cell(c,r,displaychar);	// construct cell
			// Call appropriate constructor based on display character
			switch (displaychar) {
				case '@':
					if (classtype == "k") {
					  player = new Player(&(grid[r][c]), Player::Knight);                                      
					  Orc::setHostile(true);
					  Dragon::setHostile(true);
					  Merchant::setHostile(false);
					  GridBug::setHostile(true);
					  Goblin::setHostile(true);				
					} else if (classtype == "s" ) {
					  player = new Player(&(grid[r][c]),Player::Samurai);
					  // set enemies to non-hostile default for samurai
					  Orc::setHostile(false);
					  Dragon::setHostile(false);
					  Merchant::setHostile(false);
					  GridBug::setHostile(false);
					  Goblin::setHostile(false);				
					} else if (classtype == "w") {
					  player = new Player(&(grid[r][c]), Player::Wizard);
					  Orc::setHostile(true);
					  Dragon::setHostile(true);
					  Merchant::setHostile(false);
					  GridBug::setHostile(true);
					  Goblin::setHostile(true);				
					} else if (classtype == "New Floor") {
						player->SetLocation(&(grid[r][c]));
						player->resetStats();										    
					}
					break;
				case '0':						// create restore health
				case '1':						// create boost attack
				case '2':						// create boost defense
				case '3':						// create poison health
				case '4':						// create wound attack
				case '5':						// create wound defense
						objects.push_back(new Potion(&(grid[r][c]),displaychar));
					break;
				case '6':						// create gold pile
						objects.push_back(new Treasure(&(grid[r][c]),displaychar));
					break;
				case '7':						// create dragon horde
						objects.push_back(new Treasure(&(grid[r][c]),displaychar));
						DragonHordes.push_back((Treasure*)(grid[r][c]._contents));
					break;
				case 'X':						// create grid bug
						objects.push_back(new GridBug(&(grid[r][c])));
					break;
				case 'g':						// create goblin
						objects.push_back(new Goblin(&(grid[r][c])));
					break;
				case 'M':						// create merchant
				        objects.push_back(new Merchant(&(grid[r][c])));
					break;
				case 'O':						// create orc
						objects.push_back(new Orc(&(grid[r][c])));
					break;
				case 'D':						// create dragon
				        objects.push_back(new Dragon(&(grid[r][c]), 0));
				        Dragons.push_back(grid[r][c]._contents);
					break;
			}  // switch
		}  // cols
		if ( Floor == 5 && r == HEIGHT-1 ) break;
		while ( board->peek() != '|' ) board->get();			// Continue reading board until next row of map found
	}  // rows

	// Adding neighbours to all interactable area cells
	for ( int r = 3 ; r < 22 ; ++r ) {
		for ( int c = 3 ; c < 76 ; ++c ) {
			grid[r][c].neighbours.push_back(&(grid[r-1][c-1]));
			grid[r][c].neighbours.push_back(&(grid[r-1][c]));
			grid[r][c].neighbours.push_back(&(grid[r-1][c+1]));
			grid[r][c].neighbours.push_back(&(grid[r][c-1]));
			grid[r][c].neighbours.push_back(&(grid[r][c+1]));
			grid[r][c].neighbours.push_back(&(grid[r+1][c-1]));
			grid[r][c].neighbours.push_back(&(grid[r+1][c]));
			grid[r][c].neighbours.push_back(&(grid[r+1][c+1]));
		}
	}

	// Find a horde for each dragon
	for (unsigned int i = 0 ; i < Dragons.size() ; ++i) {
		// Cycle through list of hordes
		for (unsigned int j = 0 ; j < DragonHordes.size() ; ++j) {
			// If x and y coordinates are both within 1 of the Dragon's
			if ((std::abs (DragonHordes[j]->x() - Dragons[i]->x()) <= 1) &&
				(std::abs (DragonHordes[j]->y() - Dragons[i]->y()) <= 1)) {
					((Dragon* )Dragons[i])->_treasure = DragonHordes[j];		// Add the Horde to the Dragon
					break;
			}
		}
	}	

	// Generate player, stairs, monsters, items

	// Temporary location to be used for spawns
	std::vector<int> SpawnHere;

	// Spawn Player
	SpawnHere = Spawner();
	if (classtype == "k") {
	  player = new Player(&(grid[SpawnHere[0]][SpawnHere[1]]),Player::Knight);
	  Orc::setHostile(true);
	  Dragon::setHostile(true);
	  Merchant::setHostile(false);
	  GridBug::setHostile(true);
	  Goblin::setHostile(true);			
	} else if (classtype == "s" ) {
	  player = new Player(&(grid[SpawnHere[0]][SpawnHere[1]]),Player::Samurai);
	  // set enemies to non-hostile default
	  Orc::setHostile(false);
	  Dragon::setHostile(false);
	  Merchant::setHostile(false);
	  GridBug::setHostile(false);
	  Goblin::setHostile(false);

	} else if (classtype == "w") {
	  player = new Player(&(grid[SpawnHere[0]][SpawnHere[1]]),Player::Wizard);
	  Orc::setHostile(true);
	  Dragon::setHostile(true);
	  Merchant::setHostile(false);
	  GridBug::setHostile(true);
	  Goblin::setHostile(true);			
	  
	} else if (classtype == "New Floor") {
		player->SetLocation(&(grid[SpawnHere[0]][SpawnHere[1]]));
		player->resetStats();
	}

	// Spawn Stairs
	SpawnHere = Spawner(SpawnHere[2]);					// Special call so stairs don't spawn in player's room
	grid[SpawnHere[0]][SpawnHere[1]]._display = '>';
	grid[SpawnHere[0]][SpawnHere[1]].ObjCanOcc = false;
	
	
	// Spawn Potions
	for ( int i = 0 ; i < 10 ; ++i ) {
		int PotionType = prng(5);
		while ((grid[SpawnHere[0]][SpawnHere[1]]).display() != '.') {
			SpawnHere = Spawner();	// reroll til empty
		}
		objects.push_back(new Potion(&(grid[SpawnHere[0]][SpawnHere[1]]),'0' + PotionType));
	}

	// spawn gold piles
	for (int i=0; i<10 ;i++){
	  int goldType = prng(7);
	  if(goldType <= 6){
	    
	    while((grid[SpawnHere[0]][SpawnHere[1]]).display() != '.'){
	      SpawnHere = Spawner();
	    }
	    
	    objects.push_back(new Treasure(&(grid[SpawnHere[0]][SpawnHere[1]]), '0' + goldType));
	  }
	  else{
	    bool placed = false;
	    while(!placed){

	      while((grid[SpawnHere[0]][SpawnHere[1]]).display() != '.'){
		SpawnHere = Spawner();
	      }
	  
	      Cell *goldLocation = &(grid[SpawnHere[0]][SpawnHere[1]]);
	    
	      std::vector<Cell*> DragonOptions;
	      for(int i=0; i<8; i++){
		if(goldLocation->neighbours[i]->ObjCanOcc){
		  DragonOptions.push_back(goldLocation->neighbours[i]);
		}
	      }
	      if (DragonOptions.size() == 0){ //no place to put dragon; reroll
		continue;
	      }
	     
	      int placeDragon = prng(DragonOptions.size()-1); //select one of available spots to place dragon
	      Treasure * treasure = new Treasure(goldLocation, '0' + goldType);
	      Dragon * dragon = new Dragon(DragonOptions[placeDragon], treasure);
	      objects.push_back(treasure);
	      objects.push_back(dragon);
	      placed = true;
	    }// end while; end placing dragon + dragon hoard
	  }//end else; 
	}// end for

	// spawn enemies!
	for(int i=0; i<20; i++){
	  int enemyType = prng(5) + 1; // 1 to 6
	  SpawnHere = Spawner();
	  while ((grid[SpawnHere[0]][SpawnHere[1]]).display() != '.') {
	    SpawnHere = Spawner();  // reroll til empty               
	  }
	  
	  if(enemyType <= 2)
	    objects.push_back(new GridBug(&(grid[SpawnHere[0]][SpawnHere[1]])));
	  else if (enemyType <= 4)
	    objects.push_back(new Goblin(&(grid[SpawnHere[0]][SpawnHere[1]])));
	  else if (enemyType == 5)
	    objects.push_back(new Orc(&(grid[SpawnHere[0]][SpawnHere[1]])));
	  else if (enemyType == 6)
	    objects.push_back(new Merchant(&(grid[SpawnHere[0]][SpawnHere[1]])));
	}

	// Print the board;
	print();

	// Let cc3k file know if this is not the first floor
	if (Floor > 1) throw error( "New Floor" );
}

// tick calls tick on every grid cell
void Game::tick() {

	// Loop twice to clear away items and bodies, call tick, then clear again.
	for (int i = 0 ; i < 2 ; ++i) {

		// Clear away used items and dead monsters
		for (unsigned int i = 0 ; i < objects.size(); ++i) {
			if (objects[i]->health() <= 0) {
				char deadguy = objects[i]->display();			// temporarily store appearance
				Cell* location = objects[i]->_location;			// and location of corpse/item

				// Print message
				if (deadguy != '!' && deadguy != '$') {
					std::cout << "The " << objects[i]->name() << " has died." << std::endl;
				}  // if

				// Empty the Cell
				location->AddObject(0);
				delete objects[i];
				objects.erase(objects.begin() + i);

				// Spawn Gold Pile or Potion on the deceased
				switch (deadguy) {
					case 'g':
					case 'M':
					case 'O':
						objects.push_back( new Treasure(location,'6') );		// spawn gold pile
						break;
					case 'X':
						char randompotion = '0' + prng(5);
						objects.push_back(new Potion(location, randompotion) );	// spawn potion
				}  // switch
			}  // if
		}  // for

		// Break on second loop
		if (i == 1) break;

		// call tick on every cell
		for (int r = 0 ; r < HEIGHT ; ++r) {
			for (int c = 0 ; c < WIDTH ; ++c) {
				grid[r][c].tick();
			}  // cols
		}  // rows

	}  // loop twice

	// reset tick boolean for each object
	for (unsigned int i = 0 ; i < objects.size() ; ++i) {
		objects[i]->DoTick = true;
	}

}

// Character movement command
void Game::move(int dir) {

	// Load next floor if moving onto stairs
	if (player->_location->neighbours[dir]->display() == '>') {
		Floor += 1;
		if (Floor == 6) throw error("Won");
		cout << "You descend down to floor " << Floor << "." << endl;
		NewFloor("New Floor");									//// Will have to reset attack and defence later in NewFloor
		return;
	}

	Cell* newhome = player->_location->neighbours[dir];

	if (newhome->PlayerCanOcc) {						// Check if tile is free
		newhome->AddObject(player);
		player->_location->AddObject(0);
		player->_location = newhome;
		std::string direction;
		switch (dir){
			case 0:
				direction = "north-west";
				break;
			case 1:
				direction = "north";
				break;
			case 2:
				direction = "north-east";
				break;
			case 3:
				direction = "west";
				break;
			case 4:
				direction = "east";
				break;
			case 5:
				direction = "south-west";
				break;
			case 6:
				direction = "south";
				break;
			case 7:
				direction = "south-east";
				break;
		}
		cout << "You move " << direction << "." << endl;
		turns += 1;
	} else if (newhome->display() == '$') {				// Collect gold pile if moving towards it
		newhome->_contents->use(player);
		turns += 1;
	} else {
		throw error( "You can't move in that direction." );
	}
}

// Character use command
void Game::use(int dir) {
	Cell* location = player->_location->neighbours[dir];
	switch (location->display()) {
		case '$':
		case '!':
		case 'M':
			location->_contents->use(player);
			break;
		default:
			throw error("Nothing there to use.");
	}
	turns += 1;
}

// Character attack command
void Game::attack(int dir) {
	player->PlayerAttack(dir);
	turns += 1;
}

// print out the display
void Game::print() {

	// Call tick() on all objects if this isn't a first print of this floor
	if (Tick) 
	  tick();
	Tick = true;	   // set false again by NewFloor()

	// Print the board
    for ( int r = 0 ; r < HEIGHT ; ++r ) {
    	for ( int c = 0; c < WIDTH ; ++c ) {
    		cout << grid[r][c].display();
    	}
    	cout << endl;
    }

    // Print statistics under board
	if (player != 0) {
	    cout << std::left << "        Class: " << std::setw(12) << player->name()
	    << "GP: " << std::setw(15) << GP;
	    cout << "Floor " << std::setw(7) << Floor << endl;    
	    cout << "        HP: " << std::setw(15) 
	    << std::to_string(player->health()) + "/" + std::to_string(player->maxhealth());
	    cout << "Atk: " << std::setw(14) << player->attack();
	    cout << "Def: " << std::setw(8) << std::to_string(player->defence()) + "%";
	    cout << "Turn: " << std::setw(7) << turns << endl << endl;
	}

	// Ask player for next move - This appears even if player is dead in cc3k-sample
    cout << "What will you do?" << endl;

    // Check if player dead and stopdeath not activated
    if (player->health() == 0 && !stopdeath) throw error( "Dead" );

    // Increment player health by 5 since not dead
	player->ModHealth(5);

}  // print
