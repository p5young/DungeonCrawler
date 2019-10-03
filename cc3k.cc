#include "PRNG.h"
#include "game.h"
#include "defmap.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

// Translate a command into a numerical direction
int direction(string& s) {
	if (s == "nw") {
		return 0;
	} else if (s == "no") {
		return 1;
	} else if (s == "ne") {
		return 2;
	} else if (s == "we") {
		return 3;
	} else if (s == "ea") {
		return 4;
	} else if (s == "sw") {
		return 5;
	} else if (s == "so") {
		return 6;
	} else if (s == "se") {
		return 7;
	} else {
		return -1;
	}
}

// Returns true if a string is composed entirely of digits, false otherwise
bool is_number(const std::string& s) {
	if (s.empty()) return false;
    bool number = true;
    for ( unsigned int i = 0 ; i < s.length() ; ++i ) {
    	if (!isdigit(s[i])) {
    		number = false;
    	}
    }
    return number;
}

// Declare global variables and constants
PRNG prng;										// random number generator
uint32_t seed;
int WIDTH = 79;									// height of boars
int HEIGHT = 25;								// width of board
istream* board;									// istream to read board from
int GP = 0;										// Gold Pieces
bool stopdeath = false;							// Cheat to stop player death
bool stopwander = false;						// Cheat top stop enemy movement

// Main program
int main (int argc, char *argv[] ) {
    seed = prng.seed();// store starting seed for resets
    start:	// used for restarting the game

	// Program Variables
	string classtype;							// Character class
	std::istringstream defmap(defmapstring);	// convert string default map into istream
	board = &defmap;							// initialize istream to read board from
	board->exceptions( ios_base::failbit );		// set board to throw exceptions

	// Welcome page
	cout << "Welcome to ChamberCrawler3000!" << endl
	<< "What would you like to play as today?" << endl
	<< "w) Wizard" << endl
	<< "k) Knight" << endl
	<< "s) Samurai" << endl;
	for (;;) {
		cin >> classtype;
		if ( cin.fail() ) {						// If user gives EOF as input
			return 0;							// TERMINATE PROGRAM - Use return instead of exit to avoid memory leak
		} else if ( classtype == "w" ) {
			cout << "You have chosen to play as a Wizard. Good luck." << endl;
			break;
		} else if ( classtype == "k" ) {
			cout << "You have chosen to play as a Knight. Good luck." << endl;
			break;
		} else if ( classtype == "s" ) {
			cout << "You have chosen to play as a Samurai. Good luck." << endl;
			break;																	// break;
		} else {																	// If user gives unacceptable input
			cout << "Did not recognize input." << endl;
		}
	}  // for

	// Construct Game
	Game game = Game( classtype );

	// Run the game
	try {
		for ( ;; ) {
			string command;
			cin >> command;
			if (cin.fail()) throw error( "EOF detected" );

			if (direction(command) != -1) {									// if command is a valid direction
				try {
					game.move(direction(command));
					game.print();
				} catch (error err) {
					if (err.msg.compare("Dead") == 0) {
						throw error(err.msg);
					} else if (err.msg.compare("Won") == 0) {
						throw error(err.msg);
					} else if (err.msg.compare("New Floor") == 0) {
						continue;
					}
					cout << "You can't move in that direction." << endl;
				}
			} else if (command == "a") {									// if command is an attack
				cin >> command;
				if (cin.fail()) throw error( "EOF detected");

				if (direction(command) != -1) {
					try {
						game.attack(direction(command));
						game.print();
					} catch (error err) {
						if (err.msg.compare("Dead") == 0) {
							throw error(err.msg);
						}
						cout << "There is nothing there to attack!" << endl;
					}
				} else {
					cout << "Unexpected direction for attack." << endl;
				}
			} else if (command == "u") {									// if command is a use
				cin >> command;
				if (cin.fail()) throw error( "EOF detected");

				if (direction(command) != -1) {
					try {
						game.use(direction(command));
						game.print();
					} catch (error err) {
						if (err.msg.compare("Dead") == 0) {
							throw error(err.msg);
						}
						cout << "There is nothing there to use!" << endl;
					}
				} else {
					cout << "Unexpected direction for use." << endl;
				}
			} else if (command == "stopwander" ) {							// stopwander cheat activated
				stopwander = true;
				cout << "Enemy actions that would result in movement now do nothing instead." << endl;
				game.Tick = false;
				game.print();
			} else if (command == "stopdeath") {							// stopdeath cheat activated
				stopdeath = true;
				cout << "Player death can no longer occur." << endl;
				game.Tick = false;
				game.print();
			} else if (command == "q"){
			  cout << "Are you sure you want to quit? (y/n)" << endl;
			  while(true){
			    cin >> command;
			    if (cin.fail()) throw error( "EOF detected");
			    if(command == "y"){
			      cout << "You have chosen to exit. At least you tried." << endl;
			      exit(0);
			    }
			    else if(command == "n") {
			      game.print();
			      break;
			    }
			    else 
			      cout << "Did not recognize input." << endl;
			  }
			}
			else if (command == "r"){
			  cout << "Are you sure you want to restart? (y/n)" << endl;
			  while(true){
			    cin >> command;
                if (cin.fail()) throw error( "EOF detected");
                if(command == "y"){
			      if ( board != &defmap ) delete board;
			      GP = 0;
			      prng.seed(seed); //reseed
                              goto start;
                            }
                            else if(command == "n") {
                              game.print();
                              break;
                            }
                            else
                              cout << "Did not recognize input." << endl;
			  }
			}
			else{                    // Command unacceptable
				cout << "Did not recognize input." << endl;
			}  // if

		}  // for
	} catch (error err) {
		if (err.msg.compare("EOF detected") == 0) {
			cout << "You have chosen to exit. At least you tried." << endl;
		} else {
			if (err.msg.compare("Dead") == 0) {
				cout << "You have been bested by the Great Cavernous Chambers. ";
				cout << "Good luck next time!" << endl;
			} else  if (err.msg.compare("Won") == 0) {
				cout << "At long last, you have outmatched the Great Cavernous Chambers. ";
				cout << "Great things await you." << endl;
			}
			cout << "You achieved a score of " << GP << "." << endl;
			cout << "Play again? (y/n)" << endl;
			try {
				for ( ;; ) {	
					string command;
					cin >> command;
					if (cin.fail()) throw error(err.msg);
					if (command == "y") {
						if ( board != &defmap ) delete board;
						GP = 0;
						prng.seed(seed); //reseed
						goto start;										// RESTART GAME
					} else if (command == "n") {
						throw error(err.msg);							// TERMINATE GAME
					} else {
						cout << "Did not recognize input." << endl;		// Politely tell user they're bad at typing
					}  // if
				}  // for
			} catch (error err) {
				if (err.msg.compare("Won") != 0) {
					cout << "You have chosen to exit. At least you tried." << endl;	
				}  // if
			}  // try
		}  // if
	}  // try

	// delete the infile "board"
	if ( board != &defmap ) delete board;
}
