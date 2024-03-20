#include <iostream>
#include <vector>
#include "../Observer/Observer.h"


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
    
    Cell() {
	x = 0; 
	y = 0; 
	type = EMPTY; 
    }

    Cell(int inp_x, int inp_y) {
	x = inp_x; 
	y = inp_y; 
	type = EMPTY; 
    }

    Cell(int inp_x, int inp_y, int inp_type) {
	x = inp_x; 
	y = inp_y; 
	type = inp_type; 
    }

};

typedef struct Cell Cell;


class Map : public Subject{
public:

    Map ();
    Map (Map *map);
    Map (int inp_width, int inp_height);
    Map (int inp_width, int inp_height, string inp_name);
    
    string getName();
    void setName(string inp_name);

    int getWidth();
    int getHeight();

    bool setCell(int x, int y, int type);
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

private:
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
 
};

