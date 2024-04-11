#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>


Game::Game() {
    map_index = 0;
    d20 = Dice(20);
    d6 = Dice(6);
}


bool Game::loadCampaign(string filename){
    Campaign loaded_campaign;
    loaded_campaign.setName(filename);
    
    MapMaker mapMaker;
    Map map1 = mapMaker.makeMap1();
    loaded_campaign.push_back(map1);
    
    Map map2 = mapMaker.makeMap2();
    loaded_campaign.push_back(map2);


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

Map Game::MapMaker::makeMap1(){
    Map map1(10, 7);
    map1.setName("Map 1: Intro");
    MapEditor mapEditor(&map1);
    mapEditor.setEnd(8, 3);
    mapEditor.drawSquare(0,1,4,5,WALL);
    mapEditor.drawSquare(4,0,9,6,WALL);
    mapEditor.drawSquare(4,2,4,4,EMPTY);
    mapEditor.setStart(0, 3);

    return *mapEditor.saveMap();
}

Map Game::MapMaker::makeMap2(){
    MapEditor mapEditor;
    Map map2(26, 11);
    map2.setName("Map 2: The Dungeon");
    mapEditor.setMap(&map2);
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

    mapEditor.setStart(0, 5);
    return *mapEditor.saveMap();
}


bool Game::insertCharacters(){
    vector<Character>::iterator it;
    for (auto it = characters.begin(); it != characters.end(); it++){
	Character character = *it;
	Cell start = map.getStart();
	Cell location = map.getNearbyUnnocupied(start.x, start.y);
	if (location.x == -1){
	    cout << "No space for character!\n";
	    return false;
	}
	character.setX(location.x);
	character.setY(location.y);
	character.determineSymbol();
	character.activate();
	*it = character;
	map.setCell(location.x, location.y, OCCUPIED, &*it); 

	
    }
    return true;
}

bool Game::insertEnemies(int num_enemies){
    enemies.clear();
    for (int i=0; i < num_enemies; i++){
	Enemy enemy;
	enemies.push_back(enemy);
    }

    std::srand(std::time(0));
    vector<Enemy>::iterator it;
    int min_x = map.getStart().x + 5;
    int max_x = map.getEnd().x - 3;
    for (auto it = enemies.begin(); it != enemies.end(); it++){
	Enemy enemy = *it;
	bool foundLocation = false;
	int interations = 0;
	while (!foundLocation && interations < 10000){
	    interations++;
	    int x = std::rand() % (max_x - min_x + 1) + min_x;
	    int y = std::rand() % (map.getHeight() - 1);
	    if (map.passable(x, y) && map.reachable(x, y)){
		enemy.setX(x);
		enemy.setY(y);
		enemy.determineSymbol();
		enemy.activate();
		*it = enemy;
		cout << "went through enemy loop!\n";
		map.setCell(x, y, OCCUPIED, &*it);
		foundLocation = true;
	    } 
	    
	}
	if (!foundLocation){
	    cout << "No space for enemy!\n";
	    return false;
	}
    }


    return true;
}

bool Game::loadNextMap(){
    if (map_index >= campaign.len()){
	return false;
    } 

    map = campaign.get(map_index);
    cout << "Loaded map: " << map.getName() << "!\n";
    map_index++;
    insertCharacters();
    insertEnemies(3);
    return true;
}

bool Game::gameIsPlaying(){
    bool playing = false;
    for (Character& character : characters){
	if (character.isActive()){
	    playing = true;
	}
    }

    return playing;
}
void Game::initiativePhase(){
    for (Character& character : characters){
	if (character.isActive()){
	    cout << character.getName() << ": roll for initiative (press enter)";
	    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	    character.initiativeRoll = d20.Roll();
	    cout << "You rolled a " << character.initiativeRoll << "!\n";
	}
    }

    cout << "Press enter to continue.";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}



void Game::startGameLoop(){
    bool done = false;
    while (!done && gameIsPlaying()){
	gameLoop();
	cout << "End of turn.\n";
	cout << "Enter to continue, anything else to save and exit.\n";
	string input;
	input = cin.get();
	input = cin.get();
	if (input == "\n"){
	    done = false;
	} else {
	    done = true;
	}
    }

}

void Game::gameLoop(){

    displayCurrentMap();

    initiativePhase();

    for (int i=20; i > 0; i--){
	for (Character& character : characters){
	    if (character.initiativeRoll == i && character.isActive()){
		userTurn(character);
	    }
	}
    }

}


vector<Enemy> Game::enemiesNearby(Character& character){
    vector<Enemy> nearby;
    for (Enemy& enemy : enemies){
	int dx = abs(character.getX() - enemy.getX());
	int dy = abs(character.getY() - enemy.getY());
	if (dx <= 1 && dy <= 1){
	    nearby.push_back(enemy);
	}
    }

    return nearby;
}

void Game::displayCurrentMap(){
    for (int i=0; i < 20; i++){
	cout << endl;
    }
    map.displayMap();
}

void Game::userTurn(Character& character){
    for (int i=0; i < 10; i++){
	cout << endl;
    }
    displayCurrentMap();
    cout << character.getName() << "'s (" << character.getName()[0] << ") turn!\n";

    cout << "Would you like to move? (y/n)\n";
    string move;
    cin >> move;
    cin.get();
    if (move == "y"){
	userMove(character);
    } 

    cout << "Would you like to attack? (y/n)\n";
    string attack;
    cin >> attack;
    if (attack == "y"){
	userAttack(character);
    }

}

bool Game::moveOneSquare(int dx, int dy, Character& character, Map& map){
    vector<Enemy> nearby = enemiesNearby(character);
    if (nearby.size() > 0){
	cout << "You cannot move while enemies are nearby!\n";
	return false;
    }
    
    int currentX = character.getX();
    int currentY = character.getY();
    int newX = currentX + dx;
    int newY = currentY + dy;
    if (map.getEnd().x == newX && map.getEnd().y == newY){
	map.setCell(currentX,currentY,EMPTY);
	cout << character.name << " has reached the end of the map!" << endl;
	cout << "Press enter to continue: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return false;
    }


    if(map.passable(newX,newY)){
        map.setCell(newX,newY,OCCUPIED, &character);
	character.setX(newX);
	character.setY(newY);
        map.setCell(currentX,currentY,EMPTY);
        return true;
    }

    return false;
}


bool Game::moveTo(int x, int y, Character& character, Map& map, int& spaces){
    int dx = x - character.getX();
    int dy = y - character.getY();
    int x_iterator = dx / abs(dx); 
    int y_iterator = dy / abs(dy);
    if (dx != 0 && dy != 0){
	cerr << "Invalid move direction. Can't move diagonaly.\n";
    }
    while (character.getX() != x || character.getY() != y){
	if (!moveOneSquare(x_iterator, y_iterator, character, map)){
	    cout << "Hit a wall!\n";
	    return false;
	} 


	displayCurrentMap();
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	spaces--;

	x += x_iterator;
	y += y_iterator;

    }
    
    return true;
}


void Game::userMove(Character& character){


    cout << "Roll for movement (press enter): ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //int roll = d10.Roll();
    int roll = 20;
    cout << "You rolled a " << roll << "!\n";
    bool done = false;
    while (roll > 0 && !done && character.isActive()){
	int x = character.getX();
	int y = character.getY();
	cout << "Would you like to move up, down, left, right, or exit? \n(u/d/l/r/e): ";
	string direction;
	cin >> direction;
	cout << "How many spaces would you like to move?\n#: ";
	int spaces;
	int choice;
	    
	if (direction != "e"){

	    cin >> spaces;
	}
	else {
	    spaces = 0;
	}
	choice = spaces;
	if (direction == "u" && roll - spaces >= 0){
	    moveTo(x, y - spaces, character, map, spaces);

	    roll -= choice - spaces;
	    cout << "moves left: " << roll << endl;
	} else if (direction == "d" && roll - spaces >= 0){
	    moveTo(x, y + spaces, character, map, spaces);

	    roll -= choice - spaces;
	    cout << "moves left: " << roll << endl;

	} else if (direction == "l" && roll - spaces >= 0){

	    moveTo(x - spaces, y, character, map, spaces);

	    roll -= choice - spaces;
	    cout << "Moves left: " << roll << endl;

	} else if (direction == "r" && roll - spaces >= 0){
	    moveTo(x + spaces, y, character, map, spaces);

	    roll -= choice - spaces;
	    cout << "Moves left: " << roll << endl;


	} else if (direction == "e"){
	    done = true;
	} else {
	    cout << "Invalid move, try again\n";
	}


    }
}


void Game::userAttack(Character& character){
    vector<Enemy> nearby = enemiesNearby(character);
    if (nearby.size() == 0){
	cout << "No enemies nearby to attack!\n";
	return;
    }


}
