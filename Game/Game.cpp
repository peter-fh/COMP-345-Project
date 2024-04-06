#include "Game.h"


Game::Game() {
    map_index = 0;
    d20 = Dice(20);
    d6 = Dice(6);
}


bool Game::loadCampaign(string filename){
    Campaign loaded_campaign;
    loaded_campaign.setName(filename);
    
    Map map1(10, 7);
    map1.setName("Map 1: Intro");
    MapEditor mapEditor(&map1);
    mapEditor.setEnd(8, 3);
    mapEditor.drawSquare(0,1,4,5,WALL);
    mapEditor.drawSquare(4,0,9,6,WALL);
    mapEditor.drawSquare(4,2,4,4,EMPTY);

    mapEditor.setStart(0, 3);
    /* mapEditor.drawCell(1, 2, WALL);
    mapEditor.drawCell(1, 4, WALL);
    mapEditor.drawCell(0, 1, EMPTY);
    mapEditor.drawCell(0, 5, EMPTY); */
    loaded_campaign.push_back(*mapEditor.saveMap());


    Map map2(26, 11);
    mapEditor.setMap(&map2);
    mapEditor.setStart(2, 5);
    mapEditor.setEnd(23, 5);
    mapEditor.drawSquare(0,3,6,7,WALL);
    mapEditor.drawSquare(3,0,11,3,WALL);
    mapEditor.drawSquare(8,3,11,10,WALL);
    mapEditor.drawSquare(8,7,16,10,WALL);
    mapEditor.drawSquare(13,3,16,10,WALL);
    mapEditor.drawSquare(13,3,25,7,WALL);
    mapEditor.drawSquare(18,1,22,9,WALL);
    mapEditor.drawSquare(22,3,25,7,WALL);
    mapEditor.drawSquare(4,3,5,3,EMPTY);
    mapEditor.drawSquare(9,3,10,7,EMPTY);
    mapEditor.drawSquare(11,8,13,9,EMPTY);
    mapEditor.drawSquare(14,7,15,7,EMPTY);
    mapEditor.drawSquare(14,4,24,6,EMPTY);
    mapEditor.drawSquare(19,2,21,8,EMPTY);
    mapEditor.drawSquare(20,3,20,7,EMPTY);
    mapEditor.drawSquare(14,5,22,5,EMPTY);
    loaded_campaign.push_back(*mapEditor.saveMap());


    //loaded_campaign.display_campaign();
    campaign = loaded_campaign;
    
    Character character1(1);
    Character character2(1);
    Character character3(1);

    character1.setName("Jack");
    character2.setName("Gill");
    character3.setName("Fred");

    characters.push_back(character1);
    cout << "Loaded character: " << character1.getName() << "!\n";
    characters.push_back(character2);
    cout << "Loaded character: " << character2.getName() << "!\n";
    characters.push_back(character3);
    cout << "Loaded character: " << character3.getName() << "!\n";

    cout << "Loaded campaign: " << filename << "!\n";

    return true;
    
}


bool Game::loadNextMap(){
    if (map_index >= campaign.len()){
	return false;
    } 

    map = campaign.get(0);
    cout << "Loaded map: " << map.getName() << "!\n";
    map_index++;
    map.insertCharacters(&characters);
    return true;
}


void Game::initiativePhase(){
    for (Character& character : characters){
	cout << character.getName() << ": roll for initiative (press enter)";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	character.initiativeRoll = d20.Roll();
	cout << "You rolled a " << character.initiativeRoll << "!\n";
    }

    cout << "Press enter to continue.";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}



void Game::startGameLoop(){
	gameLoop();
}

void Game::gameLoop(){
    displayCurrentMap();
    initiativePhase();
    for (int i=20; i > 0; i--){
	for (Character& character : characters){
	    if (character.initiativeRoll == i){
		
		character = userTurn(character);
	    }
	}
    }
}

void Game::displayCurrentMap(){
	map.displayMap();
}

Character Game::userTurn(Character character){
    for (int i=0; i < 10; i++){
	cout << endl;
    }
    displayCurrentMap();
    cout << character.getName() << "'s (" << character.getName()[0] << ") turn!\n";

    cout << "Would you like to move? (y/n)\n";
    string move;
    cin >> move;
    if (move == "y"){
	userMove(&character);
    } 

    /* cout << "Would you like to attack? (y/n)\n";
    string attack;
    cin >> attack;
    if (attack == "y"){
	userAttack(&character);
    }*/

    return character;
}

void Game::userMove(Character* character){


    cout << "Roll for movement (press enter): ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int roll = d6.Roll();
    cout << "You rolled a " << roll << "!\n";
    bool done = false;
    while (roll > 0 && !done){
	int x = character->getXlocation();
	int y = character->getYlocation();
	cout << "Would you like to move up, down, left, right, or exit? \n(u/d/l/r/e): ";
	string direction;
	cin >> direction;
	cout << "How many spaces would you like to move?\n#: ";
	int spaces;
	    
	if (direction != "e"){

	    cin >> spaces;
	}
	else {
	    spaces = 0;
	}
	if (direction == "u" && roll - spaces >= 0){
	    if (character->moveTo(x, y-spaces, &map)){
		displayCurrentMap();
		roll -= spaces;
	    } else {
		cout << "Invalid move, try again\n";
	    
	    }
	} else if (direction == "d" && roll - spaces >= 0){
	    if (character->moveTo(x, y + spaces, &map)){
		displayCurrentMap();
		roll -= spaces;
	    } else {
		cout << "Invalid move, try again\n";
	    
	    }

	} else if (direction == "l" && roll - spaces >= 0){
	    if (character->moveTo(x - spaces, y, &map)){
		displayCurrentMap();
		roll -= spaces;
	    } else {
		cout << "Invalid move, try again\n";
	    
	    }

	} else if (direction == "r" && roll - spaces >= 0){
	    if (character->moveTo(x + spaces, y, &map)){
		displayCurrentMap();

		roll -= spaces;
	    } else {
		cout << "Invalid move, try again\n";
	    
	    }

	} else if (direction == "e"){
	    done = true;
	} else {
	    cout << "Invalid move, try again\n";
	}


    }
}


void Game::userAttack(Character* character){
	cout << "attack logic here\n";
}
