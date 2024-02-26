#include <iostream>
#include <vector>
using namespace std;


struct Cell {
    int x;
    int y;
    
    Cell() {x = 0; y = 0;}
    Cell(int inp_x, int inp_y) {x = inp_x; y = inp_y;}
};

typedef struct Cell Cell;


const int EMPTY = 0;
const int WALL = 1;
const int OCCUPIED = 2;
const int START = 3;
const int END = 4;

class Map 
{

    vector<vector<int> > mapArray;
    void breadthFirstSearch(vector<vector<int> > *map, Cell start_cell);
    void displaySearchMap(vector<vector<int> > *map);
 
public:
    Cell start;
    Cell end;
    int width;
    int height; 
    bool setCell(Cell cell, int value);
    int getCell(Cell cell);    
    bool passable(Cell cell); 
    Map (int inp_width, int inp_height, Cell inp_start, Cell inp_end)
    {
	width = inp_width;
	height = inp_height;
	start = inp_start;
	end = inp_end;
	for (int x=0; x < width; x++){
	    vector<int> column (height);
	    fill(column.begin(), column.end(), EMPTY);
	    mapArray.push_back(column);
	}
	if (start.x >= width || start.y >= height || start.x < 0 || start.y < 0){
	    cout << "Invalid start space given to map\n";
	    start.x = 0;
	    start.y = 0;
	}

	
	if (end.x >= width || end.y >= height || end.x < 0 || end.y < 0){
	    cout << "Invalid end space given to map\n";
	    end.x = width - 1;
	    end.y = height - 1;
	}
	
	setCell(start, START);
	setCell(end, END);
    }
    bool validate();
    void displayMap();
};
