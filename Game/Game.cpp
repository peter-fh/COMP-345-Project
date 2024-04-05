#include "Game.h"


Game::Game() {
    campaign = nullptr;
}


bool Game::load(string filename){
    Campaign loaded_campaign;
    loaded_campaign.setName(filename);
    
    Map map1(10, 7);
    map1.setName("Map 1: Intro");
    MapEditor mapEditor(&map1);
    mapEditor.setStart(1, 3);
    mapEditor.setEnd(8, 3);
    mapEditor.drawSquare(0,1,4,5,WALL);
    mapEditor.drawSquare(4,0,9,6,WALL);
    mapEditor.drawSquare(4,2,4,4,EMPTY);
    loaded_campaign.push_back(*mapEditor.saveMap());


    Map map2(26, 11);
    mapEditor.setMap(&map2);
    mapEditor.setStart(2, 5);
    mapEditor.setEnd(23, 5);
    mapEditor.drawSquare(0,3,6,7,WALL);
    mapEditor.drawSquare(3,0,11,3,WALL);
    mapEditor.drawSquare(8,3,11,10,WALL);
    mapEditor.drawSquare(8,7,16,10,WALL);
    mapEditor.drawSquare(13,3,16,10,WALL);
    mapEditor.drawSquare(13,3,25,7,WALL);
    mapEditor.drawSquare(18,1,22,9,WALL);
    mapEditor.drawSquare(22,3,25,7,WALL);
    mapEditor.drawSquare(4,3,5,3,EMPTY);
    mapEditor.drawSquare(9,3,10,7,EMPTY);
    mapEditor.drawSquare(11,8,13,9,EMPTY);
    mapEditor.drawSquare(14,7,15,7,EMPTY);
    mapEditor.drawSquare(14,4,24,6,EMPTY);
    mapEditor.drawSquare(19,2,21,8,EMPTY);
    mapEditor.drawSquare(20,3,20,7,EMPTY);
    mapEditor.drawSquare(14,5,22,5,EMPTY);
    loaded_campaign.push_back(*mapEditor.saveMap());


    loaded_campaign.display_campaign();


    return true;
    
}
