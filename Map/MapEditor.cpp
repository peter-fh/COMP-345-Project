#include "MapEditor.h"

MapEditor::MapEditor(){}
MapEditor::MapEditor(Map* inp_map) {
    editedMap = inp_map;
}


bool MapEditor::drawCell(int x, int y, int type){
    return editedMap->setCell(x, y, type);
}

bool MapEditor::drawSquare(int x1, int y1, int x2, int y2, int type){
    
    if (!editedMap->checkBounds(x1, y1))
	std::cout << "First point is out of bounds.\n";

    if (!editedMap->checkBounds(x2, y2))
	std::cout << "Second point is out of bounds.\n";
    if (!editedMap->checkBounds(x1, y1) || !editedMap->checkBounds(x2, y2)){
	std::cout << "One of the given points is out of bounds\n";
	return false;
    }

    bool returnBool = true;

    if (x1 > x2){
	int temp = x1;
	x1 = x2;
	x2 = temp;
    }

    if (y1 > y2){
	int temp = y1;
	y1 = y2;
	y2 = temp;
    }


    for (int x=x1; x <= x2; x++){
	returnBool = returnBool && editedMap->setCell(x, y1, type);
	returnBool = returnBool && editedMap->setCell(x, y2, type);
    }

    for (int y=y1; y <= y2; y++){
	returnBool = returnBool && editedMap->setCell(x1, y, type);
	returnBool = returnBool && editedMap->setCell(x2, y, type);
    }


    return returnBool;

}

bool MapEditor::setStart(int x, int y){
    return editedMap->setStart(x, y);
}

bool MapEditor::setEnd(int x, int y){
    return editedMap->setEnd(x, y);
}

Map *MapEditor::saveMap(){
    return editedMap;
}

