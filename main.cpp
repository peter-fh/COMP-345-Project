#include <cassert>
#include <iostream>
#include "Map/MapEditorCLI.h"
#include "Character/CharUI.h"
#include "Dice/Dice.h"
#include "Observer/Logger.h"
#include "Character/CharacterBuilder.cpp"
#include "Character/Character.h"
#include "Enemy/Enemy.h"
#include "Enemy/Combat.h"
#include <iostream>
#include "Game/Game.h"


int main(){
    // Game game;
    // game.loadCampaign("test_campaign"); 
    // game.loadNextMap();
    // //game.startGameLoop();
    // game.loadNextMap();
    // game.startGameLoop();

    Game game;
    game.loadCampaign("test_campaign"); 
    game.loadNextMap();
    game.startGameLoop();
    game.loadNextMap();
    game.startGameLoop(); 

    Character welcome(1);
    // welcome.printCharacter();
    welcome.setName("James");
    welcome.setHP(10);
    welcome.heal();
    Armor armor1("iron chestplate","chestplate", 20);
    Weapon weapon1(3,"sword");
    Armor armor2("leather boots","boots", 10);





    welcome.pickup(&armor1);
    welcome.pickup(&weapon1);
    welcome.pickup(&armor2);


    welcome.equip(&armor1);
    welcome.equip(&weapon1);
    welcome.equip(&armor2);


    welcome.inventoryCheck();


    welcome.saveCharacter();

    Character myChar = Character::loadCharacter("James.txt");
    // myChar.printCharacter();
    myChar.inventoryCheck();



    // Map map1(10, 7);
    // map1.setName("Intro");
    // MapEditor mapEditor(&map1);
    // mapEditor.setEnd(8, 3);
    // mapEditor.drawSquare(0,1,4,5,WALL);
    // mapEditor.drawSquare(4,0,9,6,WALL);
    // mapEditor.drawSquare(4,2,4,4,EMPTY);
    // mapEditor.setStart(0, 3);

    // Cell start = map1.getStart();
    // Cell location = map1.getNearbyUnnocupied(start.x, start.y);

    // map1.displayMap();


    // Map map2(26, 11);
    // map2.setName("The Dungeon");
    // mapEditor.setMap(&map2);
    // mapEditor.setEnd(23, 5);
    // mapEditor.drawSquare(0,3,6,7,WALL);
    // mapEditor.drawSquare(3,0,11,3,WALL);
    // mapEditor.drawSquare(8,3,11,10,WALL);
    // mapEditor.drawSquare(8,7,16,10,WALL);
    // mapEditor.drawSquare(13,3,16,10,WALL);
    // mapEditor.drawSquare(13,3,25,7,WALL);
    // mapEditor.drawSquare(18,1,22,9,WALL);
    // mapEditor.drawSquare(22,3,25,7,WALL);
    // mapEditor.drawSquare(4,3,5,3,EMPTY);
    // mapEditor.drawSquare(9,3,10,7,EMPTY);
    // mapEditor.drawSquare(11,8,13,9,EMPTY);
    // mapEditor.drawSquare(14,7,15,7,EMPTY);
    // mapEditor.drawSquare(14,4,24,6,EMPTY);
    // mapEditor.drawSquare(19,2,21,8,EMPTY);
    // mapEditor.drawSquare(20,3,20,7,EMPTY);
    // mapEditor.drawSquare(14,5,22,5,EMPTY);
    // mapEditor.setStart(0, 5);

    // start = map2.getStart();
    // location = map2.getNearbyUnnocupied(start.x, start.y);

    
    // map2.displayMap();

    // map1.saveMap();

    // Map myMap = Map::loadMap("Intro.txt");
    // myMap.displayMap();

    // map2.saveMap();

    // myMap = Map::loadMap("The Dungeon.txt");
    // myMap.displayMap();    
}
