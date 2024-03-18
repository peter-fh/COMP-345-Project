#include <iostream>
#include <vector>
#include "../Map/myEL/MySubject.h"
#include "../Character/Character.h"


using namespace std;


const int EMPTY = 0;
const int WALL = 1;
const int OCCUPIED = 2;
const int START = 3;
const int END = 4;

struct Cell {
    int x;
    int y;
    int type;
    Character *character;
    
    Cell() {
	x = 0; 
	y = 0; 
	type = EMPTY; 
	character = nullptr;
    }

    Cell(int inp_x, int inp_y) {
	x = inp_x; 
	y = inp_y; 
	type = EMPTY; 
	character = nullptr;
    }

    Cell(int inp_x, int inp_y, int inp_type) {
	x = inp_x; 
	y = inp_y; 
	type = inp_type; 
	character = nullptr;
    }

    Cell(int inp_x, int inp_y, int inp_type, Character* inp_character) {
	x = inp_x; 
	y = inp_y; 
	type = inp_type; 
	character = inp_character;
    }

};


typedef struct Cell Cell;


class Map : public MySubject{
    string name;
    Cell start;
    Cell end; 
    bool initialized;
    int width;
    int height; 

    vector< vector<Cell> > mapArray;
    vector< Cell *> characterCells;

    void breadthFirstSearch(vector <vector<int> > *map, Cell start_cell);
    void displaySearchMap(vector <vector<int> > *map);
 
public:

    Map(int x);
    Map ();
    Map (Map *map);
    Map (int inp_width, int inp_height);
    Map (int inp_width, int inp_height, string inp_name);
    
    string getName();
    void setName(string inp_name);

    int getWidth();
    int getHeight();

    bool setCell(int x, int y, int type);
    bool setCell(int x, int y, int type, Character character);
    bool setCell(Cell inp_cell);
    Cell getCell(int x, int y);    

    bool setStart(int x, int y);
    Cell getStart();
    Cell getEnd();
    bool setEnd(int x, int y);

    bool checkBounds(int x, int y);
    bool passable(int x, int y); 

    bool validate();
    void displayMap();

};

