#include <cassert>
#include "Map/MapEditorCLI.h"
#include "Character/CharUI.h"
#include "Dice/Dice.h"
#include "Observer/Logger.h"
#include "Character/CharacterBuilder.cpp"
#include "Character/Character.h"
#include <iostream>


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


    // Create a Bully fighter
    BullyCharacterBuilder *bullyBuilder = new BullyCharacterBuilder(1);
    bullyBuilder->buildAbilityScores();
    Character *bully = bullyBuilder->getCharacter();

    // Create a Nimble fighter
    NimbleCharacterBuilder *nimbleBuilder = new NimbleCharacterBuilder(1);
    nimbleBuilder->buildAbilityScores();
    Character* nimble = nimbleBuilder->getCharacter();

    // Create a Tank fighter
    TankCharacterBuilder *tankBuilder = new TankCharacterBuilder(1);
    tankBuilder->buildAbilityScores();
    Character* tank = tankBuilder->getCharacter();

    // Print details of each character
    std::cout << "Bully Fighter:\n";
    bully->printCharacter();
    std::cout << "\n\n";

    std::cout << "Nimble Fighter:\n";
    nimble->printCharacter();
    std::cout << "\n\n";

    std::cout << "Tank Fighter:\n";
    tank->printCharacter();
    std::cout << "\n\n";

    // Clean up memory
    delete bullyBuilder;
    delete bully;
    delete nimbleBuilder;
    delete nimble;
    delete tankBuilder;
    delete tank;

    Character character2(1);

    CharUI playerUI(&character2);

    Weapon w1 = Weapon(10, "Sword");
    Weapon w2 = Weapon(15, "Hammer");
    Armor Chestpiece = Armor("Iron Chestplate", "Chestplate", 20);

    character2.pickup(&w1);
    character2.pickup(&w2);
    character2.pickup(&Chestpiece);

    character2.equip(0);
    character2.equip(1);
    character2.equip(2);
    character2.equip(0);
}
