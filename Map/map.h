#pragma once
#include "Cell.h"
#include "../Character/Character.h"
#include <vector>

using namespace std;


class Map {
 
public:

    std::vector<Mappable*> onMapSection; 

    
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
    bool setCell(int x, int y, int type, Mappable* mappable_obj);
    bool setCell(Cell inp_cell);
    Cell getCell(int x, int y);    

    bool setStart(int x, int y);
    Cell getStart();
    Cell getEnd();
    bool setEnd(int x, int y);

    bool checkBounds(int x, int y);
    bool passable(int x, int y); 
    bool reachable(int x, int y);
    bool isOccupied(int x, int y);
    Cell getNearbyUnnocupied(int x, int y);
    bool addMappable(Mappable* mappable_obj);
    bool insertCharacters(vector<Character*> *characters);

    bool validate();
    string toString();

    void displayMap();

    void saveMap();

    static Map loadMap(string filename);



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

