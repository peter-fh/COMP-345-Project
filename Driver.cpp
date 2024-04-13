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

class Driver {

public:
    Driver(){}
    void run(){
	mapEditor.editorLoop();
    }

private:
    Game game;
    MapEditorCLI mapEditor;

    void playDefaultGame();
    void playGame(string filename);
    void makeCharacters();
    void makeMap();

};

int main(){
    Driver driver;
    driver.run();
    return 0;
}
