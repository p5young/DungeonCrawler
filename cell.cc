#include "cell.h"

// Initializer constructor, all non-values
Cell::Cell() {
	_x = -1;
	_y = -1;
	_display = ' ';
	_contents = 0;
	ObjCanOcc = true;
	PlayerCanOcc = true;
}

// Constructor
Cell::Cell(int c, int r, char display) {
	_x = c;
	_y = r;
	_display = display;
	_contents = 0;
	ObjCanOcc = false;
	PlayerCanOcc = false;
	
	// if char display is a GameObject, set the cell's _display to '.' to become floor tile later
	switch (display) {
		case '@':
		case 'X':
		case 'g':
		case 'M':
		case 'O':
		case 'D':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
			_display = '.';
	}

	if (_display == '.') {
		PlayerCanOcc = true;
		ObjCanOcc = true;
	}
	else if (_display == '+' || _display == '#' || _display == '>') {
		PlayerCanOcc = true;
	}

}

GameObject* Cell::FindPlayer() {
  for (unsigned int i = 0 ; i < 8 ; ++i) {
    if (neighbours[i]->display() == '@') return neighbours[i]->contents();
  }
  return 0;
}

GameObject* Cell::contents() {
	return _contents;
}

int Cell::x() const {
	return _x;
}

int Cell::y() const {
	return _y;
}

char Cell::display() const {
	if (_contents == 0) return _display;
	return _contents->display();
}

void Cell::tick() {
	if (_contents != 0) 
	  _contents->tick();
}

// Add GameObject to Cell
void Cell::AddObject(GameObject* obj) {
	_contents = obj;
	if ( obj == 0 ) {
		ObjCanOcc = true;
		PlayerCanOcc = true;
		if (_display == '+' || _display == '#') ObjCanOcc = false;
	} else {
		ObjCanOcc = false;
		PlayerCanOcc = false;
	}
}
