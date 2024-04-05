#include <iostream>
#include <map>
#include "Map.h"
using namespace std;

//create empty square map
Map::Map(int x){
    name = "";
    width = x;
    height = x;

    for (int x=0; x < width; x++){
	vector<Cell> column (height);
	for (int y=0; y < height; y++){
	    column.push_back(Cell(x, y, EMPTY));
	}
	mapArray.push_back(column);
    }

}

Map::Map(){
    name = "";
    width = 2;
    height = 2;
    
    for (int x=0; x < width; x++){
	vector<Cell> column (height);
	for (int y=0; y < height; y++){
	    column.push_back(Cell(x, y, EMPTY));
	}
	mapArray.push_back(column);
    }
    setStart(0, 0);
    setEnd(width - 1, height - 1);
}


Map::Map(int inp_width, int inp_height, string inp_name){
    name = inp_name;
    width = inp_width;
    height = inp_height;
    
    for (int x=0; x < width; x++){
	vector<Cell> column (height);
	for (int y=0; y < height; y++){
	    column.push_back(Cell(x, y, EMPTY));
	}
	mapArray.push_back(column);
    }   
    
    setStart(0, 0);
    setEnd(width - 1, height - 1);
}


Map::Map(int inp_width, int inp_height)
{
    name = "Unnamed";
    width = inp_width;
    height = inp_height;
    
    for (int x=0; x < width; x++){
	vector<Cell> column (height);
	for (int y=0; y < height; y++){
	    column.push_back(Cell(x, y, EMPTY));
	}
	mapArray.push_back(column);
    }    
    setStart(0, 0);
    setEnd(width - 1, height - 1);
}


Map::Map(Map *map){
    name = map->name;
    width = map->width;
    height = map->height;
    start = map->start;
    end = map->end;
    mapArray = map->mapArray;
}


string Map::getName(){
    return name;
}


void Map::setName(string inp_name){
    name = inp_name;
    //Notify();
}


int Map::getWidth(){
    return width;
}


int Map::getHeight(){
    return height;
}


bool Map::setCell(int x, int y, int type){
    Cell inp_cell = Cell(x, y, type);
    int prev_cell_type = getCell(x, y).type;
    if (prev_cell_type  == START || prev_cell_type == END)
	return false;

    mapArray[inp_cell.x][inp_cell.y] = inp_cell;
    //Notify();
    return true;

}


bool Map::setCell(Cell inp_cell){
    int prev_cell_type = getCell(inp_cell.x, inp_cell.y).type;
    if (prev_cell_type  == START || prev_cell_type == END)
	return false;

    mapArray[inp_cell.x][inp_cell.y] = inp_cell;
    //Notify();
    return true;
}


bool Map::setCell(int x, int y, int type, Character character){
    int prev_cell_type = getCell(x, y).type;
    if (prev_cell_type == START || prev_cell_type == END)
	return false;

    Cell new_cell = Cell(x, y, type, &character);
    //character.setLocation(new_cell);
    mapArray[x][y] = new_cell;
    //Notify();
    return true;
}


Cell Map::getCell(int x, int y){
    return mapArray[x][y];
}

string Map::toString(){
    string output = "";
    map<int, string> cell_map;
    vector<vector<int> > reachable = fillValidateMap();
    cell_map[EMPTY] = "□";
    cell_map[WALL] = "■";
    cell_map[OCCUPIED] = "▣";
    cell_map[START] = "◰";
    cell_map[END] = "◲";
    

    for (int y=0; y < height; y++){
	for (int x=0; x < width; x++){
	    int type = getCell(x, y).type;
	    if (reachable[x][y] || type != EMPTY){
		output += cell_map[type] + " ";
	    } else {
		output += "  ";
	    }
	}
	output += "\n";
    }

    return output;
}


void Map::displayMap(){
    cout << "\n";
    cout << toString();
}

bool Map::setStart(int x, int y){
    bool returnBool;
    returnBool = true;
    if (x >= width || y >= height || x < 0 || y < 0){
	cout << "Invalid start space given to map (line 144)\n";
	x = 0;
	y = 0;
	returnBool = false;
    }    
   
    mapArray[start.x][start.y] = Cell(start.x, start.y, EMPTY);
    start = Cell(x, y, START);
    mapArray[x][y] = start;
    //Notify();
    return returnBool;
}


bool Map::setEnd(int x, int y){
    bool returnBool;
    returnBool = true;
    if (x >= width || y >= height || x < 0 || y < 0){
	cout << "\nInvalid end space given to map.\n";
	x = 0;
	y = 0;
	returnBool = false;
    }
    
    mapArray[end.x][end.y] = Cell(end.x, end.y, EMPTY);
    end = Cell(x, y, END);
    mapArray[x][y] = end;
    //Notify();
    return returnBool;
}


bool Map::checkBounds(int x, int y){
    if (x >= width || x < 0 || y >= height || y < 0)
	return false;

    return true;
}

bool Map::passable(int x, int y){
    int cell_type = getCell(x, y).type;

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

    breadthFirstSearch(&searchMap, Cell(start.x, start.y));

    if (searchMap[end.x][end.y] == REACHED)
	return true;

    return false;
}

vector<vector<int> > Map::fillValidateMap(){
    vector<vector<int> > searchMap;
    // Fill entire map with unreached
    for (int x = 0; x < width; x++){
	vector<int> column (height);
	fill(column.begin(), column.end(), UNREACHED);
	searchMap.push_back(column);
    }

    breadthFirstSearch(&searchMap, Cell(start.x, start.y));

    return searchMap;
}


void Map::breadthFirstSearch(vector<vector<int> > *map, Cell start_cell){
    int x = start_cell.x;
    int y = start_cell.y;
    map->at(x)[y] = REACHED;

    // Search left
    if (x > 0 && map->at(x-1)[y] == UNREACHED && passable(x-1, y)){
	breadthFirstSearch(map, Cell(x-1, y));
    }
    // Search right
    if (x < width - 1){
	if (map->at(x+1)[y] == UNREACHED && passable(x+1, y))
	    breadthFirstSearch(map, Cell(x+1, y));
    }
    // Search down
    if (y > 0 && map->at(x)[y-1] == UNREACHED && passable(x, y-1)){
	breadthFirstSearch(map, Cell(x, y-1));
    }
    // Search up
    if (y < height - 1 && map->at(x)[y+1] == UNREACHED && passable(x, y+1)){
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


// int main(){
//
//     Map map (20, 20, Cell(0, 0), Cell(19, 19));
// 	
//     for (int y = 0; y < map.height; y++)
//     map.setCell(Cell(14, y), WALL);
//
//     map.setCell(Cell(14, 17), EMPTY);
//     map.displayMap();
//     cout << map.validate() << "\n";
//     return 0;
// }
