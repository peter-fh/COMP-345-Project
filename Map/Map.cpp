#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Map.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/Corpse.h"
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


bool Map::setCell(int x, int y, int type, Mappable* mappable){
    int prev_cell_type = getCell(x, y).type;
    if (prev_cell_type == START || prev_cell_type == END){
	return false;
    }

    Cell new_cell = Cell(x, y, type, mappable);
    mapArray[x][y] = new_cell;
    return true;
}



Cell Map::getCell(int x, int y){
    return mapArray[x][y];
}

Cell Map::getStart(){
    return start;
}

Cell Map::getEnd(){
	return end;
}

string Map::toString(){
    string output = "";
    Textures textures;
    for (int y=0; y < height; y++){
	for (int i=0; i < 6; i++){
	    for (int x=0; x < width; x++){
		int type = getCell(x, y).type;
		if (!reachable(x, y) && type == EMPTY){
		    output += "          ";
		} else if (type == START){
		    output += textures.start[i];
		} else if (type == END){
		    output += textures.end[i];
		} else if (type == WALL){
		    output +=textures.wall[i];
		} else if (type == EMPTY){
		    output +=textures.empty[i];
		} else if (type == OCCUPIED && getCell(x, y).mappable_obj != nullptr){
		    if (getCell(x, y).mappable_obj->getSymbol() == 'P'){
			output +=textures.character[i];
		    }
		    if (getCell(x, y).mappable_obj->getSymbol() == 'E'){
			output +=textures.enemy[i];
		    }
		    if (getCell(x, y).mappable_obj->getSymbol() == 'X'){
			output +=textures.bag[i];
		    }
		} 
		output += " ";
	    }
	    output += "\n";
	}
    }
    return output;
}

string Map::toStringOld(){
    string output = "";
    map<int, string> cell_map;
    vector<vector<int> > reachable = fillValidateMap();
    cell_map[EMPTY] = "□";
    cell_map[WALL] = "■";
    cell_map[OCCUPIED] = "▣";
    cell_map[START] = "◰";
    cell_map[END] = "◲";
    
    /* //for testing and viewing the map on my end -Eric
    cell_map[EMPTY] = "0";
    cell_map[WALL] = "W";
    cell_map[OCCUPIED] = "X";
    cell_map[START] = "S";
    cell_map[END] = "F"; */
    
    for (int y=0; y < height; y++){
	for (int x=0; x < width; x++){
	    int type = getCell(x, y).type;
	    if (type == END){
		output += cell_map[type] + " ";
	    } else if (reachable[x][y] || type != EMPTY){
		if (type == OCCUPIED && getCell(x, y).mappable_obj != nullptr){ 
		    Mappable* mappable = getCell(x, y).mappable_obj;
		    char symbol = mappable->getSymbol();
		    if (!isalpha(symbol)){
			cerr << "Error: Mappable object does not have a valid symbol\n";
		    }
		    output.push_back(symbol);
		    output += " ";
		} else {
		    if (type == OCCUPIED && getCell(x, y).mappable_obj== nullptr){
			cerr << "Error: OCCUPIED cell with no character\n";
		    }
		    output += cell_map[type] + " ";
		}
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


bool Map::isOccupied(int x, int y){
    return getCell(x, y).type == OCCUPIED || getCell(x, y).type == START || getCell(x, y).type == END;
}


Cell Map::getNearbyUnnocupied(int x, int y){
    Cell N(x, y-1);
    Cell NE(x+1,y-1);
    Cell E(x+1,y);
    Cell SE(x+1,y+1);
    Cell S(x, y+1);
    Cell SW(x-1, y+1);
    Cell W(x-1,y+1);
    Cell NW(x-1,y-1);

    if (checkBounds(N.x, N.y) && passable(N.x, N.y) && !isOccupied(N.x, N.y)){
	return N;
    }

    if (checkBounds(NE.x, NE.y) && passable(NE.x, NE.y) && !isOccupied(NE.x, NE.y)){
	return NE;
    }

    if (checkBounds(E.x, E.y) && passable(E.x, E.y) && !isOccupied(E.x, E.y)){
	return E;
    }

    if (checkBounds(SE.x, SE.y) && passable(SE.x, SE.y) && !isOccupied(SE.x, SE.y)){
	return SE;
    }

    if (checkBounds(S.x, S.y) && passable(S.x, S.y) && !isOccupied(S.x, S.y)){
	return S;
    }

    if (checkBounds(SW.x, SW.y) && passable(SW.x, SW.y) && !isOccupied(SW.x, SW.y)){
	return SW;
    }

    if (checkBounds(W.x, W.y) && passable(W.x, W.y) && !isOccupied(W.x, W.y)){
	return W;
    }

    if (checkBounds(NW.x, NW.y) && passable(NW.x, NW.y) && !isOccupied(NW.x, NW.y)){
	return NW;
    }

    return Cell(-1, -1);


}

bool Map::insertCharacters(vector<Character*> *characters){
    vector<Mappable*>::iterator it;
    for (auto it = characters->begin(); it != characters->end(); it++){
	Mappable* mappable = *it;
	Cell location = getNearbyUnnocupied(start.x, start.y);
	if (location.x == -1){
	    cout << "No space for mappable\n";
	    return false;
	}
	mappable->setX(location.x);
	mappable->setY(location.y);
	mappable->activate();
	setCell(location.x, location.y, OCCUPIED, mappable); // WARN: this might not work
	
    }
    return true;
}


bool Map::checkBounds(int x, int y){
    if (x >= width || x < 0 || y >= height || y < 0)
	return false;

    return true;
}

bool Map::passable(int x, int y){
    int cell_type = getCell(x, y).type;

    if (cell_type == EMPTY || cell_type == START || cell_type == END || cell_type == OCCUPIED){
	return true;
    }

    return false;
}

const int REACHED = 1;
const int UNREACHED = 0;

bool Map::reachable(int inp_x, int inp_y){
    
    vector<vector<int> > searchMap;
    // Fill entire map with unreached
    for (int x = 0; x < width; x++){
	vector<int> column (height);
	fill(column.begin(), column.end(), UNREACHED);
	searchMap.push_back(column);
    }

    breadthFirstSearch(&searchMap, Cell(start.x, start.y));

    if (searchMap[inp_x][inp_y] == REACHED){
	return true;
    }

    return false;
}


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


bool Map::addMappable(Mappable* mappable_obj){
    int x = mappable_obj->getX();
    int y = mappable_obj->getY();
    if (passable(x, y)){
	setCell(x, y, OCCUPIED, mappable_obj);
	return true;
	}
	return false;
}

void Map::saveMap() {
    std::ofstream file(getName()+ ".txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file0 for saving." << std::endl;
        return;
    }
    file << getWidth() << "," << getHeight() << std::endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Cell cell = getCell(x, y);
            // if (cell.character != nullptr) {
            //     file << cell.character->getName(); // Ensure getName() only returns a simple identifier
            // }
            // else{
                file << cell.type;
            // }
            
            file << (x == width - 1 ? '\n' : ',');
        }
    }
    file.close();
}

Map Map::loadMap(string filename){
    Map map;
    std::ifstream file(filename);
    std::string line;

    if (std::getline(file, line)) { // Read the first line
        std::istringstream iss(line);
        std::string value;
        int width, height;

        // Get first value
        std::getline(iss, value, ',');
        width = std::stoi(value);

        // Get second value
        std::getline(iss, value, ',');
        height = std::stoi(value);

        map = Map(width,height,filename.substr(0, filename.size() - 4));
    }

    int col = 0;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string cell;
            int row = 0;

            while (std::getline(iss, cell, ',')) {
                try {
                    // Attempt to convert cell to an integer
                    // std::cout<<cell<<endl;
                    int cellType = std::stoi(cell);

                    // If conversion succeeds, it's a number
                    if (cellType == 3) { // START
                        map.setStart(row, col);
                    } else if (cellType == 4) { // END
                        map.setEnd(row, col);
                    } else {
                        map.setCell(row, col, cellType);
                    }
                } catch (std::invalid_argument const &e) { //just gotta save a class 
                    // Conversion failed, cell is a string
                    if (cell == "E") { //placing an enemy
                        Enemy testEnemy = Enemy();
                        map.setCell(row, col,2,&testEnemy);
                    }
                    else{
                        Character fromSave(10);//to be worked on
                        fromSave.setName(cell);
                        map.setCell(row, col,2,&fromSave);
                    }
                }
                row++;
            }
            col++;
        }
        file.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return map;
}
