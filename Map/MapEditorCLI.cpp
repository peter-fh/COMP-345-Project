#include "MapEditorCLI.h"


using std::cout;
using std::cin;

MapEditorCLI::MapEditorCLI() {}


Map MapEditorCLI::createMap(){
    cout << "Creating new map.\n";

    string name;
    cout << "Enter a map name: ";
    cin >> name;

    cout << "Enter the map dimentions.\n";
    
    int width;
    int height;
    cout << "Width: ";
    cin >> width;
    cout << "Height: ";
    cin >> height;

    return Map(width, height, name);
     
}



bool MapEditorCLI::setSquare(){
    cout << "Creating square.\n";
    int type;
    int x1;
    int y1;
    int x2;
    int y2;
    cout << "Type: ";
    cin >> type;
    cout << "First corner:\n";
    cout << "x: ";
    cin >> x1;
    cout << "y: ";
    cin >> y1;
    cout << "Second corner:\n";
    cout << "x: ";
    cin >> x2;
    cout << "y: ";
    cin >> y2;
    mapEditor.drawSquare(x1, y1, x2, y2, type);
    return true;
}


bool MapEditorCLI::setCell(){
    cout << "Setting cell\n";
    int type;
    int x;
    int y;
    cout << "Type: ";
    cin >> type;
    cout << "Square\n";
    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;

    mapEditor.drawCell(x, y, type);
    return true;
}


bool MapEditorCLI::setStart(){
    cout << "Setting start cell\n";
    int x;
    int y;
    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;
    mapEditor.setStart(x, y);
    return true;
}


bool MapEditorCLI::setEnd(){
    cout << "Setting end cell\n";
    int x;
    int y;
    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;
    mapEditor.setEnd(x, y);
    return true;
}


bool MapEditorCLI::loadMap(){
    string name;
    cout << "Select a map.\n";
    cout << "Name: ";
    cin >> name;

    Map* map = campaign.get(name);
    if (map == nullptr)
	return false;

    mapEditor = MapEditor(*map);
    return true;
}


bool MapEditorCLI::saveMap(){
    Map map = mapEditor.saveMap();
    return campaign.replace(map);

}


bool MapEditorCLI::saveMapAs(){
    int index;
    cout << "Enter an index for where to place map in campaign (0 for beginning, -1 for end)";

    cin >> index;

    return campaign.insert(mapEditor.saveMap(), index);
}


bool MapEditorCLI::moveMap(){
    string name;
    int index;

    cout << "Select a map and it's new index.\n";
    cout << "Map name: ";
    cin >> name;
    cout << "Index: ";
    cin >> index;

    Map* map = campaign.get(name);
    if (map == nullptr)
	return false;

    return campaign.remove(*map);
}


const int SET_CELL = 1;
const int SET_SQUARE = 2;
const int SET_START = 3;
const int SET_END = 4;
const int DISPLAY = 5;
const int EXIT = 6;

Map MapEditorCLI::mapEditorLoop(){ 
    Map initial_map = mapEditor.saveMap();
    bool exit = false;
    while (!exit){
	int userChoice;
	cout << "\n\n\nYou are editing the map " << initial_map.getName() << ".\n";
	cout << "Select one of these options:\n";
	cout << "(1) Set specific cell to certain type\n";
	cout << "(2) Set square of cells to certain type\n";
	cout << "(3) Change the start square\n";
	cout << "(4) Change the end square\n";
	cout << "(5) Display map\n";
	cout << "(6) Finish editing\n";
	cout << "Selection: #";
	cin >> userChoice;

	if (userChoice == SET_CELL){
	    cout << "Selected (1) Set square of cells to certain type\n";
	    int x;
	    int y;
	    int type;
	    cout << "Enter the coordinates of the cell.\n";
	    cout << "x: ";
	    cin >> x;
	    cout << "y: ";
	    cin >> y;
	    cout << "Types of cells: (1) Empty (2) Wall (3) Occupied\n";
	    cout << "Cell type: ";
	    cin >> type;

	    bool success = mapEditor.drawCell(x, y, type);
	    if (success) 
		cout << "Success!\n";
	    else
		cout << "Failed to draw cell. Ensure that given point is within bounds."; 
	}
	else if (userChoice == SET_SQUARE){
	    cout << "Selected (2) Set square of cells to certain type\n";
	    int x1;
	    int y1;
	    int x2;
	    int y2;
	    int type;
	    cout << "Enter the coordinates of the first corner.\n";
	    cout << "x1: ";
	    cin >> x1;
	    cout << "y1: ";
	    cin >> x2;
	    cout << "x2: ";
	    cin >> x2;
	    cout << "y2: ";
	    cin >> y2;
	    cout << "Types of cells: (1) Empty (2) Wall (3) Occupied\n";
	    cout << "Cell type: ";
	    cin >> type;

	    bool success = mapEditor.drawSquare(x1, y1, x2, y2, type);
	    if (success) 
		cout << "Success!\n";
	    else
		cout << "Failed to draw cell. Ensure that given points are within bounds.\n";


	}
	else if (userChoice == SET_START){
	    cout << "Selected (3) Set start square\n";
	    int x;
	    int y;
	    cout << "Enter the coordinates of the cell.\n";
	    cout << "x: ";
	    cin >> x;
	    cout << "y: ";
	    cin >> y;

	    bool success = mapEditor.setStart(x, y);
	    if (success) 
		cout << "Success!\n";
	    else
		cout << "Failed to set start. Check that given point is within bounds.\n";
	}

	else if (userChoice == SET_END){
	    cout << "Selected (4) Set start square\n";
	    int x;
	    int y;
	    cout << "Enter the coordinates of the cell.\n";
	    cout << "x: ";
	    cin >> x;
	    cout << "y: ";
	    cin >> y;

	    bool success = mapEditor.setEnd(x, y);
	    if (success) 
		cout << "Success!\n";
	    else
		cout << "Failed to set end. Check that given point is within bounds.\n";
	}
	else if (userChoice == DISPLAY){
	    mapEditor.saveMap().displayMap();
	}
	else if (userChoice == EXIT){
	    Map final_map = mapEditor.saveMap();
	    if (final_map.validate())
		return final_map;
	    else {
		cout << "Map is invalid: start not reachable from end.\n";
		cout << "(1) Continue editing\n";
		cout << "(2) Give up (DELETES PROGRESS!!)\n";
		int userExitChoice;
		cout << "Selection: #";
		cin >> userExitChoice;
		if (userExitChoice == 2)
		    exit = true;    
	    }
	}

    }

    return mapEditor.saveMap();
}


void MapEditorCLI::campaignEditorLoop(){
    bool exit = false;
    while (!exit){
	int userIn;
	cout << "\n\n\nNow editing campaign " << campaign.getName() << ".\n";
	cout << "Your options are:\n";
	cout << "(1) Edit map\n";
	cout << "(2) Reorder maps\n";
	cout << "(3) Create new map\n";
	cout << "(4) Display campaign\n";
	cout << "(5) Exit campaign editor\n";
	cout << "Selection: #";
	cin >> userIn;

	if (userIn == 1){
	    string userInMap;
	    cout << "Enter a map name: ";
	    cin >> userInMap;
	    Map* userMap = campaign.get(userInMap);
	    if (userMap != nullptr){
		mapEditor = MapEditor(*userMap);
		mapEditorLoop();
	    }
	    else 
		cout << "Invalid map name.\n";
	    
	}
	else if (userIn == 2){
	    moveMap();
	}
	else if (userIn == 3){
	    campaign.push_back(createMap());
	}
	else if (userIn == 4){
	     campaign.display_campaign();
	}
	else if (userIn == 5){
	    exit = true;
	}


    }
}


Campaign MapEditorCLI::editorLoop(){

    cout << "\n\n\nWelcome to the campaign editor!\n";
    cout << "Your options are:\n";
    cout << "(1) Create new campaign\n";
    cout << "(2) Load campaign from file\n";
    int userInput;
    cout << "Selection: #";
    cin >> userInput;
    if (userInput == 1){
	cout << "\n\n\nYou are now creating a new campaign!\n";
	cout << "Name your new campaign:\n"; 
	string name;
	cout << "Name: ";
	cin >> name;
	campaign = Campaign();
	campaign.setName(name);
	campaignEditorLoop();
    }
    // TODO: Add functionality to load from file
    // TODO: Add functionality to save from file

    return campaign;
}



