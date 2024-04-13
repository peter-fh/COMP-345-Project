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
    Campaign turtle = Campaign();
    turtle.setName("TT");
    Map beach = Map::loadMap("Intro.txt");
    Map jungle = Map::loadMap("The Dungeon.txt");
    Map concrete = Map::loadMap("Urban Street.txt");
    Map cloud = Map::loadMap("Sky Fort.txt");
    Map pearl = Map::loadMap("Deep Ocean.txt");

    turtle.push_back(beach);
    turtle.push_back(jungle);
    turtle.push_back(concrete);
    turtle.push_back(cloud);
    turtle.push_back(pearl);

    // turtle.display_campaign();
    turtle.saveCampaign();


    Campaign beluga = Campaign::loadCampaign("TT.txt");
    beluga.display_campaign();






    // Game game;
    // game.loadCampaign("test_campaign"); 
    // game.loadNextMap();
    // //game.startGameLoop();
    // game.loadNextMap();
    // game.startGameLoop();

//CHARACTER SAVING AND LOADING**********
    // Character welcome(1);
    // // welcome.printCharacter();
    // welcome.setName("James");
    // welcome.setHP(10);
    // welcome.heal();
    // Armor armor1("iron chestplate","chestplate", 20);
    // Weapon weapon1(3,"sword");
    // Armor armor2("leather boots","boots", 10);

    // welcome.pickup(&armor1);
    // welcome.pickup(&weapon1);
    // welcome.pickup(&armor2);

    // welcome.equip(&armor1);
    // welcome.equip(&weapon1);
    // welcome.equip(&armor2);

    // welcome.inventoryCheck();

    // welcome.saveCharacter();

    // Character myChar = Character::loadCharacter("James.txt");
    // // myChar.printCharacter();
    // myChar.inventoryCheck();
    // myChar.setName("Mike");
    // myChar.saveCharacter();
    // welcome.saveCharacter();
//CHARACTER SAVING AND LOADING**********





    // Map map1(10, 7);
    // map1.setName("Intro");
    // mapEditor.setEnd(8, 3);
    // mapEditor.drawSquare(0,1,4,5,WALL);
    // mapEditor.drawSquare(4,0,9,6,WALL);
    // mapEditor.drawSquare(4,2,4,4,EMPTY);
    // mapEditor.setStart(0, 3);

    // Cell start = map1.getStart();
    // Cell location = map1.getNearbyUnnocupied(start.x, start.y);

    // map1.displayMap();


    // Map myMap(18, 18);
    // myMap.setName("");
    // MapEditor mapEditor(&myMap);
    // mapEditor.drawSquare(a,b,c,d,EMPTY);
    // mapEditor.drawSquare(0,0,4,4,WALL);
    // mapEditor.drawSquare(0,14,4,17,WALL);
    // mapEditor.drawSquare(14,0,17,4,WALL);
    // mapEditor.drawSquare(14,14,17,17,WALL);
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
    
    // mapEditor.setEnd(8, 1);
    // mapEditor.setStart(1, 25);
// 26, 11
// setEnd(23, 5)
// setStart(0, 5)
    
    // myMap.displayMap();
    // myMap.saveMap();
    // map2.saveMap();

    // myMap = Map::loadMap("The Dungeon.txt");
    // myMap.displayMap();    
}
