#include <iostream>
#include <map>
#include "map.h"
using namespace std;


int Map::getCell(Cell cell){
    return mapArray[cell.x][cell.y];
}
bool Map::setCell(Cell cell, int type){
    int cell_type = getCell(cell);
    if (cell_type == START || cell_type == END)
	return false;

    mapArray[cell.x][cell.y] = type;
    return true;
}


void Map::displayMap(){
    map<int, string> cell_map;
    cell_map[EMPTY] = " ";
    cell_map[WALL] = "W";
    cell_map[OCCUPIED] = "O";
    cell_map[START] = "S";
    cell_map[END] = "E";
    
    cout << "\n";

    for (int x=0; x < width; x++){
	cout << x << " ";
    }

    cout << "\n";
    for (int y=0; y < height; y++){
	for (int x=0; x < width; x++){
	    cout << cell_map[getCell(Cell(x, y))] << " ";
	}
	cout << y << "\n";
    }
}

int main(){

    Map map (2, 10, Cell(-1, 0), Cell(1, 7));

    map.displayMap();
}
