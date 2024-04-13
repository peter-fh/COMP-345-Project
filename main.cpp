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

<<<<<<< HEAD
int main()
{
=======

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






>>>>>>> cd76ee04f3b307bb6b7b138c867dfa09defb2924
    // Game game;
    // game.loadCampaign("test_campaign");
    // game.loadNextMap();
    // //game.startGameLoop();
    // game.loadNextMap();
    // game.startGameLoop();

<<<<<<< HEAD
=======
//CHARACTER SAVING AND LOADING**********
>>>>>>> cd76ee04f3b307bb6b7b138c867dfa09defb2924
    // Character welcome(1);
    // // welcome.printCharacter();
    // welcome.setName("James");
    // welcome.setHP(10);
    // welcome.heal();
<<<<<<< HEAD
    // Armor armor1("iron chestplate", "chestplate", 20);
    // Weapon weapon1(3, "sword");
    // Armor armor2("leather boots", "boots", 10);
=======
    // Armor armor1("iron chestplate","chestplate", 20);
    // Weapon weapon1(3,"sword");
    // Armor armor2("leather boots","boots", 10);
>>>>>>> cd76ee04f3b307bb6b7b138c867dfa09defb2924

    // welcome.pickup(&armor1);
    // welcome.pickup(&weapon1);
    // welcome.pickup(&armor2);
<<<<<<< HEAD
=======

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
>>>>>>> cd76ee04f3b307bb6b7b138c867dfa09defb2924

    // welcome.equip(&armor1);
    // welcome.equip(&weapon1);
    // welcome.equip(&armor2);

    // welcome.inventoryCheck();
    // welcome.setX(10);
    // welcome.setY(15);
    // welcome.saveCharacter();

    // Character myChar = Character::loadCharacter("James.txt");

    // std::cout << "Character Information:" << myChar.getX() << ", " << myChar.getY() << std::endl;
    // // myChar.printCharacter();
    // myChar.inventoryCheck();

<<<<<<< HEAD
    Enemy enemy21;
    enemy21.setX(100);
    enemy21.setY(200);
    enemy21.maxHP = 20;
    enemy21.currentHP = 10;

    Armor armor1("iron chestplate", "chestplate", 20);
    Weapon weapon1(3, "sword");
    Armor armor2("leather boots", "boots", 10);

    enemy21.giveItem(&armor1);
    enemy21.giveItem(&weapon1);
    enemy21.giveItem(&armor2);

    enemy21.saveEnemy();

    // Enemy myEnemy = Enemy::loadEnemy("Goblin.txt");

    std::cout << enemy21.equippedChestplate << enemy21.getX() << std::endl;

    std::cout << "Enemy Information:" << enemy21.getX() << std::endl;

=======
>>>>>>> cd76ee04f3b307bb6b7b138c867dfa09defb2924
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

<<<<<<< HEAD
    // Map map2(26, 11);
    // map2.setName("The Dungeon");
    // mapEditor.setMap(&map2);
    // mapEditor.setEnd(23, 5);
    // mapEditor.drawSquare(0,3,6,7,WALL);
    // mapEditor.drawSquare(3,0,11,3,WALL);
    // mapEditor.drawSquare(8,3,11,10,WALL);
    // mapEditor.drawSquare(8,7,16,10,WALL);
=======

    // Map myMap(18, 18);
    // myMap.setName("");
    // MapEditor mapEditor(&myMap);
    // mapEditor.drawSquare(a,b,c,d,EMPTY);
    // mapEditor.drawSquare(0,0,4,4,WALL);
    // mapEditor.drawSquare(0,14,4,17,WALL);
    // mapEditor.drawSquare(14,0,17,4,WALL);
    // mapEditor.drawSquare(14,14,17,17,WALL);
>>>>>>> cd76ee04f3b307bb6b7b138c867dfa09defb2924
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
<<<<<<< HEAD
    // mapEditor.drawSquare(14,5,22,5,EMPTY);
    // mapEditor.setStart(0, 5);

    // start = map2.getStart();
    // location = map2.getNearbyUnnocupied(start.x, start.y);

    // map2.displayMap();

    // map1.saveMap();

    // Map myMap = Map::loadMap("Intro.txt");
=======
    
    // mapEditor.setEnd(8, 1);
    // mapEditor.setStart(1, 25);
// 26, 11
// setEnd(23, 5)
// setStart(0, 5)
    
>>>>>>> cd76ee04f3b307bb6b7b138c867dfa09defb2924
    // myMap.displayMap();
    // myMap.saveMap();
    // map2.saveMap();

    // myMap = Map::loadMap("The Dungeon.txt");
    // myMap.displayMap();
}
