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

    Game game;
    game.loadCampaign("test_campaign"); 
    game.loadNextMap();
    //game.startGameLoop();
    game.loadNextMap();
    game.startGameLoop(); 

    /* cin.get();
    cin.get();
    cin.get();
    cin.get();
    Character character2(12);
    character2.setName("Jeff");

    CharUI playerUI(&character2);

    Weapon w1 = Weapon(3, "Sword");
    Armor Chestpiece = Armor("Iron Chestplate", "Chestplate", 20);

    character2.pickup(&w1);
    character2.pickup(&Chestpiece);

    character2.equip(0);
    character2.equip(1);




    Enemy e1 = Enemy();
    e1.status();
    Enemy e2 = Enemy();
    e2.status();

    Combat(&character2, &e1);
    cout << endl;
    //system("pause"); */
}
