#include <cassert>
#include "Map/MapEditorCLI.h"
#include "Character/CharUI.h"
#include "Item/Item.cpp"
#include "Dice/Dice.h"
#include "Observer/Logger.h"


int main(){
/*     //testing Character Strategy
    HumanPlayerStrategy hs;
    AggressorStrategy as;
    FriendlyStrategy fs;
    //HumanPlayerStrategy
    Character char1(&hs);
    char1.performMoveAction();
    char1.performAttackAction();
    char1.performFreeAction();
    //AggressorStrategy
    char1.setStrategy(&as);
    char1.performMoveAction();
    char1.performAttackAction();
    char1.performFreeAction();
    //FriendlyStrategy
    char1.setStrategy(&fs);
    char1.performMoveAction();
    char1.performAttackAction();
    char1.performFreeAction();
    //Changing from FriendlyStrategy to AggressorStrategy
    //char1.takeDmg(1);
    char1.performMoveAction();
    char1.performAttackAction();
    char1.performFreeAction();
  */   

    Logger logger;
    Map* map;
    map = new Map(5, 5);
    logger.attachMap(map);
    map->Attach(&logger);
    map->setStart(0, 4);
    map->setEnd(4, 0);


    Character* character;
    character = new Character(1);
    logger.attachCharacter(character);
    character->Attach(&logger);
    character->increaseLevel(1);
    character->setHP(15);
    character->setName("John");

    CharUI playerUI(&character);

    Weapon w1 = Weapon(10, "Sword");
    Weapon w2 = Weapon(15, "Hammer");
    Armor Chestpiece = Armor("Iron Chestplate", "Chestplate", 20);

    character.pickup(&w1);
    character.pickup(&w2);
    character.pickup(&Chestpiece);

    character.equip(0);
    character.equip(1);
    character.equip(2);
    character.equip(0);


    
    Dice* dice;
    dice = new Dice(6);
    logger.attachDice(dice);
    dice->Attach(&logger);
    dice->Roll();

}
