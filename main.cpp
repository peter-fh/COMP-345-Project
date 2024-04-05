#include <cassert>
#include <iostream>
#include "Map/MapEditorCLI.h"
#include "Character/CharUI.h"
#include "Dice/Dice.h"
#include "Observer/Logger.h"
#include "Character/CharacterBuilder.cpp"
#include "Character/Character.h"
#include "Game/Game.h"


int main(){
    Game game;
    game.loadCampaign("test_campaign"); 
    game.loadNextMap();
    game.startGameLoop();
    return 0;
    
    


}
