#include "Map/MapEditorCLI.h"
#include "Map/myEL/MySubject.h"
#include "Character/CharUI.h"
#include "Dice/Dice.h"
#include "Item/Item.cpp"
#include <iostream>
using namespace std;


class MapObserver : public MyObserver {
private:
    Map* map_;
public:
    MapObserver(Map* map) : map_(map) {}
    void Update() override {
        map_->displayMap();
    }
};


int main(){
    
    cout<<"hello";
    // Create a map
    int mapSize = 10;

    Map* map = new Map(mapSize);
    // Create an observer for the map
    MapObserver* observer = new MapObserver(map);
    // Attach the observer to the map
    map->Attach(observer);

    // make some changes to the map
    map->setCell(0, 0, START);
    map->setCell(mapSize-1, mapSize-1, END);
    // set some walls
    for(int i=0;i<mapSize;i++){
        for(int j=0;j<mapSize;j++){
            if(i==j){
                map->setCell(i, j, WALL);
            }        
        }
    }
    // make things occupied
    for(int i=0;i<mapSize;i=i+2){
        for(int j=0;j<mapSize;j=j+2){
            if(i==mapSize-j){
                map->setCell(i,j, OCCUPIED);
            }        
        }
    }
    
    

    // Clean up
    delete observer;
    delete map;

 
    Character playerCharacter = Character(10);

    CharUI playerUI(&playerCharacter);
    playerCharacter.setStrength(18);


    MapEditorCLI editor = MapEditorCLI();
    editor.editorLoop();


    return 0;
}
