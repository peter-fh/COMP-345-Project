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
#include "Game/StartingUI.h"

class Driver {

public:
    Driver(){}
    void run(){
	bool exit = false;
	while (!exit){
	    cout << "Welcome to the game! Please select an option:" << endl;
	    cout << "1. Play default game" << endl;
	    cout << "2. Play saved game" << endl;
	    cout << "3. Play game with custom map" << endl;
	    cout << "4. Campaign Editor" << endl;
	    cout << "5. Character Creator" << endl;
	    cout << "6. Exit" << endl;
	    int choice;
	    cin >> choice;
	    if (choice == 1){
		playDefaultGame();
	    } else if (choice == 2){
		cout << "Enter the filename of the game you would like to play: ";
		string filename;
		cin >> filename;
		playGame(filename);
	    }
	    else if (choice == 2){
		cout << "Enter the filename of the map you would like to play: ";
		string filename;
		cin >> filename;
		playCampaign(filename);
	    }
	    else if (choice == 3){
		mapEditor.editorLoop();
	    }
	    else if (choice == 4){
		makeCharacters();
	    }
	    else if (choice == 5){
		exit = true;
	    } else {
		cout << "Invalid choice" << endl;
	    }

	}
	mapEditor.editorLoop();
    }

private:
    Game game;
    MapEditorCLI mapEditor;

    void playDefaultGame(){
	game.loadCampaign();
	game.loadNextMap();
	game.startGameLoop();
    }
    void playGame(string filename){
	game = Game::loadGame(filename);
	cout << "about to game loop" << endl;
	game.startGameLoop();
	cout << "game looped" << endl;
    }
    void playCampaign(string filename){
	game.loadCampaign(filename);
	game.startGameLoop();
    }
    void makeCharacters(){

    }

};

int main(){
    Driver driver;
    driver.run();

    return 0;
}
