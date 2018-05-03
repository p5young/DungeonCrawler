#ifndef CELL_H
#define CELL_H
#include "gameobject.h"
#include <vector>

// forward declaration because mutual reference
class GameObject;

class Cell {
    friend class GameObject;
    friend class Orc;
    friend class GridBug;
    friend class Goblin;
    friend class Dragon;
    friend class Merchant;
    friend class Player;
    friend class Game;
    // Coordinates
    int _x, _y;
    // Appearance of the Cell when _contents are empty
    char _display;
    // Contents of the Cell
    GameObject* _contents;
    // Number of Neighbours and associated array
    std::vector<Cell*> neighbours;
    
    public:

    	Cell();
        Cell(int x, int y, char display);

        GameObject* FindPlayer();
        GameObject* contents();

        int x() const;
        int y() const;
        char display() const;
        void tick();
		void AddObject(GameObject* obj);

        // These boolean values are to be checked by spawners, moving monsters, and the player when moving
        bool ObjCanOcc;
        bool PlayerCanOcc;
};

#endif
