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


    // Map* map;
    // map = new Map(5, 5);
    Character* character;
    character = new Character(1);
    //Dice dice;
    //Map* mapPtr = &map;

    // logger.attachMap(map);
    // map->Attach(&logger);
    logger.attachCharacter(character);

    character->Attach(&logger);
    //dice.Attach(&logger);

    //logger.attachDice(&dice);
    
    // map->setStart(0, 4);
    // map->setEnd(4, 0);

    character->increaseLevel(1);
    character->setHP(15);
    character->setName("John");

    
    Dice* dice;
    dice = new Dice(6);

    logger.attachDice(dice);
    dice->Attach(&logger);

    dice->Roll();

}
