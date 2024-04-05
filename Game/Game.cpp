#include "Game.h"


Game::Game() {
    campaign = nullptr;
}


bool Game::load(string filename){
    Campaign loaded_campaign;
    loaded_campaign.setName(filename);
    
    Map map1(10, 7);
    map1.setName("Map 1: intro");
    MapEditor map1Editor(&map1);
    map1Editor.setStart(1, 3);
    map1Editor.setEnd(8, 3);
    map1Editor.drawSquare(0, 1, 9, 5, WALL);
    Map *returnMap = map1Editor.saveMap(); 
    returnMap->displayMap();
    Map nonPtrMap(returnMap);
    nonPtrMap.displayMap();
    loaded_campaign.display_campaign();
    return true;
    
}
