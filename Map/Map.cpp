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


bool Map::passable(Cell cell){
    int cell_type = getCell(cell);

    if (cell_type == EMPTY || cell_type == START || cell_type == END) 
	return true;

    return false;
}


const int REACHED = 1;
const int UNREACHED = 0;


bool Map::validate(){
    vector<vector<int> > searchMap;

    // Fill entire map with unreached
    for (int x = 0; x < width; x++){
	vector<int> column (height);
	fill(column.begin(), column.end(), UNREACHED);
	searchMap.push_back(column);
    }

    
    breadthFirstSearch(&searchMap, start);
    displaySearchMap(&searchMap);

    if (searchMap[end.x][end.y] == REACHED)
	return true;

    return false;
    
}


void Map::breadthFirstSearch(vector<vector<int> > *map, Cell start_cell){
    int x = start_cell.x;
    int y = start_cell.y;
        
    map->at(x)[y] = REACHED;

    // Search left
    if (x > 0 && map->at(x-1)[y] == UNREACHED && passable(Cell(x-1, y))){
	breadthFirstSearch(map, Cell(x-1, y));
    }
    

    // Search right
    if (x < width - 1){
	if (map->at(x+1)[y] == UNREACHED && passable(Cell(x+1, y)))
	    breadthFirstSearch(map, Cell(x+1, y));
    }


    // Search down
    if (y > 0 && map->at(x)[y-1] == UNREACHED && passable(Cell(x, y-1))){
	breadthFirstSearch(map, Cell(x, y-1));
    }


    // Search up
    if (y < height - 1 && map->at(x)[y+1] == UNREACHED && passable(Cell(x, y+1))){
	breadthFirstSearch(map, Cell(x, y+1));
    }
}


void Map::displaySearchMap(vector<vector<int> > *map){
    cout << "\n";

    for (int x=0; x < width; x++){
	cout << x % 10<< " ";
    }

    cout << "\n";
    for (int y=0; y < height; y++){
	for (int x=0; x < width; x++){
	    int cell_visited = map->at(x)[y];
	    cout << cell_visited << " ";
	}
	cout << y << "\n";
    }
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
	cout << x % 10<< " ";
    }

    cout << "\n";
    for (int y=0; y < height; y++){
	for (int x=0; x < width; x++){
	    cout << cell_map[getCell(Cell(x, y))] << " ";
	}
	cout << y << "\n";
    }
}


// int main(){

//     Map map (20, 20, Cell(0, 0), Cell(19, 19));
    
//     for (int y = 0; y < map.height; y++)
// 	map.setCell(Cell(14, y), WALL);

//     map.setCell(Cell(14, 17), EMPTY);
//     map.displayMap();
//     cout << map.validate() << "\n";
//     return 0;
// }
