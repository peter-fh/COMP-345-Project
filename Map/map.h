#include <iostream>
#include <vector>

using std::vector;
using std::string;


const int EMPTY = 0;
const int WALL = 1;
const int OCCUPIED = 2;
const int START = 3;
const int END = 4;

struct Cell {
    int x;
    int y;
    int type;
    
    Cell() {x = 0; y = 0; type = EMPTY;}
    Cell(int inp_x, int inp_y) {x = inp_x; y = inp_y; type = EMPTY;}
    Cell(int inp_x, int inp_y, int inp_type) {x = inp_x; y = inp_y; type = inp_type;}
};

typedef struct Cell Cell;


class Map 
{

    std::vector<vector<Cell> > mapArray;
    string name;
    void breadthFirstSearch(vector<vector<int> > *map, Cell start_cell);
    void displaySearchMap(vector<vector<int> > *map);
 
public:
    Cell* start;
    Cell* end; 
    bool initialized;
    int width;
    int height; 
    string getName();
    void setName(string inp_name);
    bool setCell(int x, int y, int type);
    bool setCell(Cell inp_cell);
    Cell getCell(int x, int y);    
    bool passable(int x, int y); 
    bool setStart(int x, int y);
    bool setEnd(int x, int y);
    bool checkBounds(int x, int y);

    Map ();
    Map (Map *map);
    Map (int inp_width, int inp_height);
    Map (int inp_width, int inp_height, string inp_name);
    
    bool validate();
    void displayMap();
};
