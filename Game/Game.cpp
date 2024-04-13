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

    character1.setName("Jack");
    character1.setHP(10);
    character1.heal();
    player = character1;

    Weapon *w1 = new Weapon(3, "Sword");
    Armor *Chestpiece = new Armor("Iron Chestplate", "Chestplate", 20);

    player.pickup(w1);
    player.pickup(Chestpiece);

    player.equip(0);
    player.equip(1);


    cout << "Loaded character: " << character1.getName() << "!\n";

    cout << "Loaded campaign: " << filename << "!\n";

    return true;
    
}

Map Game::MapMaker::makeMap1(){
    Map map1(10, 7);
    map1.setName("Intro");
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
    map2.setName("The Dungeon");
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
    Cell start = map.getStart();
    Cell location = map.getNearbyUnnocupied(start.x, start.y);
    if (location.x == -1){
	cout << "No space for character!\n";
	return false;
    }
    player.setX(location.x);
    player.setY(location.y);
    player.determineSymbol();
    player.activate();
    map.setCell(location.x, location.y, OCCUPIED, &player); 


    return true;
}


bool Game::insertChests(int num_chests){
    chests.clear();
    for (int i=0; i < num_chests; i++){
	Chest chest;
	chests.push_back(chest);
    }
    cout << "Chest size: " << chests.size() << endl;

    std::srand(std::time(0));
    for (auto it = chests.begin(); it != chests.end(); it++){
	Chest chest = *it;
	bool foundLocation = false;
	int iterations = 0;
	int max_x = map.getWidth() - 1;
	int min_x = map.getStart().x + 1;
	while (!foundLocation && iterations < 10000){
	    iterations++;
	    int x = std::rand() % (max_x - min_x + 2) + min_x;
	    int y = std::rand() % (map.getHeight() - 1);
	    if (map.passable(x, y) && map.reachable(x, y) && !map.isOccupied(x, y)){
		chest.setX(x);
		chest.setY(y);
		chest.determineSymbol();
		*it = chest;
		map.setCell(x, y, OCCUPIED, &*it);
		foundLocation = true;
	    
	    }
	}

	if (!foundLocation){
	    cout << "No space for chest!\n";
	    return false;
	}
    }

    return true;
}


bool Game::insertEnemies(int num_enemies){
    enemies.clear();
    for (int i=0; i < num_enemies; i++){
	Enemy enemy;
	enemy.alive = true;
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
	    if (map.passable(x, y) && map.reachable(x, y) && !map.isOccupied(x, y)){
		enemy.setX(x);
		enemy.setY(y);
		enemy.determineSymbol();
		enemy.activate();
		*it = enemy;
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
    insertEnemies(1);
    insertChests(1);
    return true;
}

bool Game::gameIsPlaying(){
    return player.isActive();
}
void Game::initiativePhase(){
    if (player.isActive()){
	cout << player.getName() << ": roll for initiative (press enter)";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	player.initiativeRoll = d20.Roll();
	cout << "You rolled a " << player.initiativeRoll << "!\n";
    }
    
    for (Enemy& enemy : enemies){
	if (enemy.isActive()){
	    enemy.initiative = d20.Roll();
	    cout << enemy.status();
	    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	    cout << " rolled a " << enemy.initiative << "!\n";
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
	if (player.initiativeRoll == i){
	    userTurn(player);
	}

	for (Enemy& enemy : enemies){
	    if (enemy.initiative == i){
		enemyTurn(enemy);
	    }
	}
    }

}

void Game::enemyTurn(Enemy& enemy){
    if (moveEnemy(enemy)){
	Combat combat(player, enemy);
    }
}



vector<Chest> Game::chestsNearby(Character& character){
    vector<Chest> nearby;
    for (Chest& chest : chests){
	int dx = abs(character.getX() - chest.getX());
	int dy = abs(character.getY() - chest.getY());
	if (dx <= 1 && dy <= 1){
	    nearby.push_back(chest);
	}
    }

    return nearby;
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

    vector<Enemy> nearbyEnemies = enemiesNearby(character);
    if (nearbyEnemies.size() > 0){
	cout << "Would you like to attack? (y/n)\n";
	string attack;
	cin >> attack;
	if (attack == "y"){
	    userAttack(character);
	}
    }

    vector<Chest> nearbyChests = chestsNearby(character);
    if (nearbyChests.size() > 0){
	cout << "Would you like to open a chest? (y/n)\n";
	string open;
	cin >> open;
	if (open == "y"){
	    userLoot(nearbyChests[0]);
	}
    }


}


void Game::userLoot(Chest& chest){
    chest.openChest();
    cout << "Which item would you like to take? (1-" << chest.getNumOfContents() << ")\n";
    int choice;
    cin >> choice;
    Item* item = chest.takeItem(choice);
    if (item != nullptr){
	player.pickup(item);
    }
}

bool Game::moveEnemy(Enemy& enemy){
    int xDirection = (player.getX() - enemy.getX()) / abs(player.getX() - enemy.getX());
    int yDirection = (player.getY() - enemy.getY()) / abs(player.getY() - enemy.getY());
    cout << enemy.status() << " is rolling for movement (press enter)";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int roll = d6.Roll();
    cout << enemy.status() << " rolled a " << roll << "!\n";

    displayCurrentMap();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    while (roll > 0 && xDirection != 0){
	if (moveEnemyOneSquare(xDirection, 0, enemy, map)){
	    displayCurrentMap();
	    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	    roll--;
	    xDirection = (player.getX() - enemy.getX()) / abs(player.getX() - enemy.getX());

	} else {
	    break;
	}
    }

    while (roll > 0 && yDirection != 0){

	if (moveEnemyOneSquare(0, yDirection, enemy, map)){
	    displayCurrentMap();
	    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	    roll--;

	    yDirection = (player.getY() - enemy.getY()) / abs(player.getY() - enemy.getY());
	} else {
	    break;
	}
    }

    if (abs(enemy.getX() - player.getX()) <= 1 && abs(enemy.getY() - player.getY()) <= 1){
	return true;
    } 

    return false;



}
bool Game::moveEnemyOneSquare(int dx, int dy, Enemy& enemy, Map& map){
    
    int currentX = enemy.getX();
    int currentY = enemy.getY();
    int newX = currentX + dx;
    int newY = currentY + dy;

    if(map.passable(newX,newY) && !map.isOccupied(newX,newY)){
        map.setCell(newX,newY,OCCUPIED, &enemy);
	enemy.setX(newX);
	enemy.setY(newY);
        map.setCell(currentX,currentY,EMPTY);
        return true;
    } 

    return false;
}


bool Game::moveOneSquare(int dx, int dy, Character& character, Map& map, bool& done){
    
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


    if(map.passable(newX,newY) && !map.isOccupied(newX,newY)){
        map.setCell(newX,newY,OCCUPIED, &character);
	character.setX(newX);
	character.setY(newY);
        map.setCell(currentX,currentY,EMPTY);
        return true;
    } else {
	cout << "Hit a wall!\n";
    }

    return false;
}


bool Game::moveTo(int x, int y, Character& character, Map& map, int& spaces, bool& done){
    int dx = x - character.getX();
    int dy = y - character.getY();
    int x_iterator = dx / abs(dx);
    int y_iterator = dy / abs(dy);
    if (dx != 0 && dy != 0){
	cerr << "Invalid move direction. Can't move diagonaly.\n";
    }
    while (character.getX() != x || character.getY() != y){
	if (!moveOneSquare(x_iterator, y_iterator, character, map, done)){
	    return false;
	} 


	displayCurrentMap();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	spaces--;


    }
    
    return true;
}


void Game::userMove(Character& character){


    cout << "Roll for movement (press enter): ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // TODO: make movement actually random again
    // int roll = d10.Roll();
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
	    moveTo(x, y - spaces, character, map, spaces, done);

	    roll -= choice - spaces;
	    cout << "moves left: " << roll << endl;
	} else if (direction == "d" && roll - spaces >= 0){
	    moveTo(x, y + spaces, character, map, spaces, done);

	    roll -= choice - spaces;
	    cout << "moves left: " << roll << endl;

	} else if (direction == "l" && roll - spaces >= 0){

	    moveTo(x - spaces, y, character, map, spaces, done);

	    roll -= choice - spaces;
	    cout << "Moves left: " << roll << endl;

	} else if (direction == "r" && roll - spaces >= 0){
	    moveTo(x + spaces, y, character, map, spaces, done);

	    roll -= choice - spaces;
	    cout << "Moves left: " << roll << endl;


	} else if (direction == "e"){
	    done = true;
	} else {
	    cout << "Invalid move, try again\n";
	}


    }
}

void Game::insertCorpses(){
    for (Corpse& corpse : corpses){
	corpse.determineSymbol();
	map.setCell(corpse.getX(), corpse.getY(), OCCUPIED, &corpse);
    }
}

void Game::userAttack(Character& character){
    vector<Enemy> nearby = enemiesNearby(character);
    if (nearby.size() == 0){
	cout << "No enemies nearby!\n";
	return;
    } else {
	Enemy enemy = nearby[0];
	Combat combat(character, enemy);
	if (enemy.alive == false){
	    Corpse corpse(&enemy);
	    cout << "corpse symbol: " << corpse.getSymbol() << endl;
	    corpse.setX(enemy.getX());
	    corpse.setY(enemy.getY());
	    corpses.push_back(corpse);
	    enemies.erase(enemies.begin());
	    insertCorpses();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }


}
