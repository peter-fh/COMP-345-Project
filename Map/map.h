#pragma once
#include "Cell.h"

using namespace std;


class Map  : public Subject{
 
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
    bool setCell(int x, int y, int type, Character* character);
    bool setCell(Cell inp_cell);
    Cell getCell(int x, int y);    

    bool setStart(int x, int y);
    Cell getStart();
    Cell getEnd();
    bool setEnd(int x, int y);

    bool checkBounds(int x, int y);
    bool passable(int x, int y); 

    bool validate();
    string toString();

    void displayMap();

    //moving a character on the map
    bool addChar(Character myChar);

private:
    string name;
    Cell start;
    Cell end; 
    bool initialized;
    int width;
    int height; 

    vector< vector<Cell> > mapArray;
    //vector< Cell *> characterCells;

    void breadthFirstSearch(vector <vector<int> > *map, Cell start_cell);
    void displaySearchMap(vector <vector<int> > *map);
    vector<vector<int> > fillValidateMap();
};

