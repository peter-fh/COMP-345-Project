#include <iostream>
#include <map>
#include "map.h"
using namespace std;

string Map::getName(){
    return name;
}


Cell Map::getCell(int x, int y){
    return mapArray[x][y];
}


bool Map::setCell(int x, int y, int type){
    Cell inp_cell = Cell(x, y, type);
    int prev_cell_type = getCell(x, y).type;
    if (prev_cell_type  == START || prev_cell_type == END)
	return false;

    mapArray[inp_cell.x][inp_cell.y] = inp_cell;
    return true;

}
bool Map::setCell(Cell inp_cell){
    int prev_cell_type = getCell(inp_cell.x, inp_cell.y).type;
    if (prev_cell_type  == START || prev_cell_type == END)
	return false;

    mapArray[inp_cell.x][inp_cell.y] = inp_cell;
    return true;
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

    breadthFirstSearch(&searchMap, *start);

    if (searchMap[end->x][end->y] == REACHED)
	return true;

    return false;
    
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


void Map::displayMap(){
    map<int, string> cell_map;
    cell_map[EMPTY] = "□";
    cell_map[WALL] = "■";
    cell_map[OCCUPIED] = "▣";
    cell_map[START] = "◰";
    cell_map[END] = "◲";
    

    cout << "\n";
    for (int y=0; y < height; y++){
	for (int x=0; x < width; x++){
	    cout << cell_map[getCell(x, y).type] << " ";
	}
	cout << "\n";
    }
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
   
    if (start != nullptr)
	*start = Cell(start->x, start->y, EMPTY);
    setCell(Cell(x, y, START));
    start = &(mapArray[x][y]);
    return returnBool;
 
}


bool Map::setEnd(int x, int y){
    bool returnBool;
    returnBool = true;
    if (x >= width || y >= height || x < 0 || y < 0){
	cout << "Invalid end space given to map\n";
	x = 0;
	y = 0;
	returnBool = false;
    }
 
    if (end != nullptr)
	*end = Cell(start->x, start->y, EMPTY);

    setCell(Cell(x, y, END));
    end = &(mapArray[x][y]);
    return returnBool;
 
}


Map::Map(){
    name = "";
    width = 2;
    height = 2;
    start = nullptr;
    end = nullptr;
    
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
Map::Map(int inp_width, int inp_height, string inp_name)
{
    name = inp_name;
    width = inp_width;
    height = inp_height;
    start = nullptr;
    end = nullptr;
    
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
    start = nullptr;
    end = nullptr;
    
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
