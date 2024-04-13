#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>


Game::Game() {
    hasKey = true;
    map_index = 0;
    d20 = Dice(20);
    d6 = Dice(6);
}

bool Game::loadCampaign(string campaign_name){
    Campaign loaded_campaign = Campaign::loadCampaign(campaign_name);
    if (loaded_campaign.getName() == ""){
	cout << "Failed to load campaign.\n";
	return false;
    }
    campaign = loaded_campaign;
    cout << "Loaded campaign: " << campaign.getName() << "!\n";
    return true;
}

bool Game::loadCampaign(){
    Campaign loaded_campaign;
    loaded_campaign.setName("Default_Campaign");
    
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

    Weapon *w1 = new Weapon(10000, "Sword");
    Armor *Chestpiece = new Armor("Iron Chestplate", "Chestplate", 20);

    player.pickup(w1);
    player.pickup(Chestpiece);

    player.equip(0);
    player.equip(1);


    cout << "Loaded character: " << character1.getName() << "!\n";

    cout << "Loaded campaign: " << "Default Campaign" << "!\n";

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


bool Game::insertBags(int num_bags){
    // corpses.clear();
    for (int i=0; i < num_bags; i++){
	Armor* armor1 = new Armor("Iron Helmet", "Helmet", 12);
	Armor* armor2 = new Armor("Iron Pants","Pants", 12);
	Armor* armor3 = new Armor("Iron Chestpiece","Chestplate", 12);
	Armor* armor4 = new Armor("Iron Boots","Boots", 12);
	std::vector<Item*> v = {armor1, armor2, armor3, armor4};
	Corpse openme = Corpse(v);
	corpses.push_back(openme);
	cout << "Bag created!\n";
    }

    std::srand(std::time(0));
    for (auto it = corpses.begin(); it != corpses.end(); it++){
	Corpse chest = *it;
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

    addKey();
    return true;
}

void Game::addKey(){
    hasKey = false;
    Key* key = new Key(0);
    enemies[0].giveItem(new Key(0));
}

bool Game::loadNextMap(){
    if (map_index >= campaign.len()){
	return false;
    } 

    map = campaign.get(map_index);
    map_index++;
    insertCharacters();
    insertEnemies(1);
    cout << "Inserted enemies!\n";
    //insertChests(1);
    cout << "Loaded map: " << map.getName() << "!\n\n\n\n\n";
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

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    cout << "Press enter to continue.";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}



void Game::startGameLoop(){
    bool done = false;
    player.activate();
    while (!done && gameIsPlaying()){
	gameLoop();
	cout << "End of turn.\n";
	cout << "Enter to continue, anything else to save and exit.\n";
	string input;
	cin >> input;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (input == "\n"){
	    done = false;
	} else {
	    done = true;
	}
    }

    saveGame();

}

void Game::gameLoop(){

    displayCurrentMap();

    initiativePhase();
    
    displayCurrentMap();

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
	combat(enemy);
    }
}


vector<Corpse> Game::corpseNearby(){
    vector<Corpse> nearby;
    for (Corpse& corpse: corpses){
	int dx = abs(player.getX() - player.getX());
	int dy = abs(player.getY() - player.getY());
	if (dx <= 1 && dy <= 1){
	    nearby.push_back(corpse);
	}
    }

    return nearby;
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

    cout << "Roll for movement (press enter): ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // TODO: make movement actually random again
    // int roll = d10.Roll();
    int movement_roll = 20;
    cout << "You rolled a " << movement_roll << "!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    bool done = false;

    while (!done){

	vector<Enemy> nearbyEnemies = enemiesNearby(character);
	vector<Chest> nearbyChests = chestsNearby(character);
	vector<Corpse> nearbyCorpses = corpseNearby();
	cout << "What would you like to do?\n";
	if (movement_roll > 0){
	cout << "(m) Move: " << movement_roll << " spaces remaining\n";
	}
	if (nearbyEnemies.size() > 0){
	    cout << "(a) Attack\n";
	}
	if(nearbyChests.size() > 0){
	    cout << "(o) Open chest\n";
	}
	if(nearbyCorpses.size() > 0){
	    cout << "(l) Loot corpse\n";
	}
	cout << "(i) Open inventory\n";
	cout << "(e) End turn\n";
	string choice;
	cout << "Choice: ";
	cin >> choice;
	cin.get();
	if (choice == "m" && movement_roll > 0){
	    userMove(character, movement_roll);
	} else if (choice == "a" && nearbyEnemies.size() > 0){
	    userAttack(character);
	} else if (choice == "o" && nearbyChests.size() > 0){
	    userLoot(nearbyChests[0]);
	} else if (choice == "l" && nearbyCorpses.size() > 0){
	    userLoot(nearbyCorpses[0]);
	} else if (choice == "i"){
	    character.inventoryCheck();
	    cout << "Press enter to continue: ";
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} else if (choice == "e"){
	    done = true;
	} else if (movement_roll <= 0 && nearbyEnemies.size() == 0 && nearbyChests.size() == 0 && nearbyCorpses.size() == 0){
	    cout << "No more moves left.\n";
	    done = true;
	} else {
	    cout << "Invalid choice, try again.\n";
	}

	displayCurrentMap();

    }
    cout << "Press enter to continue: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');



}


void Game::userLoot(Chest& chest){
    displayCurrentMap();
    chest.openChest();
    cout << "Which item would you like to take? (1-" << chest.getNumOfContents() << ")\n";
    int choice;
    cin >> choice;
    Item* item = chest.takeItem(choice);
    if (item->key == true){
	hasKey = true;
    } 
    if (item != nullptr){
	player.pickup(item);
    }
}

void Game::userLoot(Corpse& corpse){
    displayCurrentMap();
    corpse.search();
    cout << "Which item would you like to take? (1-" << corpse.getInvSize() << ")\n";
    int choice;
    cin >> choice;
    Item* item = corpse.loot(choice);
    if (item != nullptr){
	if (item->key == true){
	    hasKey = true;
	}
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

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    displayCurrentMap();
    bool hasMoved = true;
    while (hasMoved){
	hasMoved = false;
	while (roll > 0 && xDirection != 0){
	    if (moveEnemyOneSquare(xDirection, 0, enemy, map)){
		hasMoved = true;
		displayCurrentMap();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		roll--;
		xDirection = (player.getX() - enemy.getX()) / abs(player.getX() - enemy.getX());

	} else {
		break;
	    }
	}

	while (roll > 0 && yDirection != 0){

	    if (moveEnemyOneSquare(0, yDirection, enemy, map)){
		hasMoved = true;
		displayCurrentMap();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		roll--;

		yDirection = (player.getY() - enemy.getY()) / abs(player.getY() - enemy.getY());
	} else {
		break;
	    }
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
	for (Item* item : character.inventory){
	    if (item->key == true || item->getItemName() == "Key"){
		cout << "key found\n";
		hasKey = true;
	    }
	}
	if (hasKey){
	    map.setCell(currentX,currentY,EMPTY);
	    cout << character.name << " has reached the end of the map!" << endl;
	    character.deactivate();
	    done = true;
	    cout << "Press enter to continue: ";
	    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    return false;
	} else {
	    cout << "You need a key to open the door!\n";
	    return false;
	}
    }


    if(map.passable(newX,newY)){
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

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	spaces--;


    }
    
    return true;
}


void Game::userMove(Character& character, int& roll){

    displayCurrentMap();
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
	    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
	combat(enemy);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));


}


void Game::combat(Enemy& enemy){
    Combat combat(player, enemy);
    if (enemy.alive == false){
	ofstream file("corpse.txt");
	file << "dead" << endl;
	Corpse corpse(&enemy);
	corpse.setX(enemy.getX());
	corpse.setY(enemy.getY());
	corpses.push_back(corpse);
	enemies.erase(enemies.begin());
	insertCorpses();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout << endl;


}

void Game::saveGame() {
    string filename;
    cout << "Enter filename to save game (including .txt!): ";
    cin >> filename;

	std::ofstream file("stuff.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file for saving." << std::endl;
        return;
    }
    file << "map_index:" << map_index<< "\n";
    file << "campaign:" << campaign.getName() << "\n";
	campaign.saveCampaign();
	// file << "map:" << map.getName() << "\n";
	// map.saveMap();
	file << "player:" << player.getName() << "\n";
	player.saveCharacter();
	file << "hasKey:" << hasKey << "\n";

	file << "\nenemy:";
	int i = 0;
    for (Enemy& enemy: enemies){
		file << i <<",";
		enemy.saveEnemy(std::to_string(i) + "enemy.txt");
		i++;
	}

    file << "\ncorpse:";
	i = 0;
    for (Corpse& corpse: corpses){
		file << i <<",";
		corpse.saveCorpse(std::to_string(i) + "corpse.txt");
		i++;
	}




}


Game Game::loadGame(string filename){
    Game theGame = Game();

    Character player;
    std::vector<Enemy> enemies;
    std::vector<Corpse> corpses;

    std::ifstream file("stuff.txt");
    std::string line;
    string map_index,campaign,playerName,hasKey;
    string enemy,corpse;

    if (!file.is_open())
    {
	cout<<"no file\n";
	throw std::runtime_error("Could not open game file");
    }

    while (getline(file, line))
    {
	std::istringstream iss(line);
	std::string key;
	if (getline(iss, key, ':'))
	{
	    cout<<key<<endl;
	    std::string value;
	    getline(iss, value);

	    if (key == "map_index")
	    {
		theGame.map_index = stoi(value);
	    }
	    else if (key == "campaign")
	    {
		cout << "loading campaign\n";
		Campaign cai = Campaign::loadCampaign(value+ ".txt");
		theGame.campaign =cai;
		theGame.map = cai.get(theGame.map_index);
		cout << "loaded campaign: " << cai.getName() << "!\n";
	    }
	    else if (key == "player")
	    {
		cout << "loading player\n";
		Character cay = Character::loadCharacter(value+".txt");
		theGame.player = cay;
		theGame.player.determineSymbol();
		theGame.player.activate();
		theGame.map.setCell(cay.getX(),cay.getY(), OCCUPIED, &theGame.player);
		cout << "loaded player: " << cay.getName() << "!\n";
	    }
	    else if (key == "hasKey")
	    {
		cout << "loading hasKey\n";
		if(stoi(value)==1){
		    theGame.hasKey = true;
		}
		else{
		    theGame.hasKey = false;
		}
		cout << "loaded hasKey: " << theGame.hasKey << "!\n";
	    }


	    else if (key == "enemy")
	    {
		cout << "loading enemy\n";
		while (getline(file, line) && !line.empty())
		{
		    std::istringstream itemStream(line);
		    std::string value;
		    getline(itemStream, value, ',');
		    try {
			stoi(value);
			cout << "loading enemy: " << value << "!\n";
			//corpse:
			Enemy emy = Enemy::loadEnemy(value+"enemy.txt");
			enemies.push_back(emy);
			enemies.back().determineSymbol();
			enemies.back().activate();
			theGame.map.setCell(emy.getX(),emy.getY(), OCCUPIED, &enemies.back());
			cout << "loaded enemy: " << enemies.back().getSymbol() << "!\n";
		    }catch (std::invalid_argument e) {
			    cout << "lol";
			}
		}
		cout << "loaded enemy. size: " << enemies.size() << "!\n";
	    }
	    else if (key == "corpse")
	    {
		cout << "loading corpse\n";
		while (getline(file, line) && !line.empty())
		{
		    std::istringstream itemStream(line);
		    std::string value;
		    getline(itemStream, value, ',');
		    Corpse cos = Corpse::loadCorpse(value+"corpse.txt");

		    corpses.push_back(cos);
		    corpses.back().determineSymbol();
		    corpses.back().activate();

		    theGame.map.setCell(cos.getX(),cos.getY(), OCCUPIED, &corpses.back());
		}
		cout << "loaded corpse: " << corpses.size() << "!\n";
	    }
	}
    }
    file.close();
    theGame.enemies = enemies;
    theGame.corpses = corpses;
    //cout << "enemy symbol at the end: " << enemies.back().getSymbol();

    return theGame;
}
