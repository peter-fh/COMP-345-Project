#include "Game.h"


Game::Game() {
    map_index = 0;
}


bool Game::loadCampaign(string filename){
    Campaign loaded_campaign;
    loaded_campaign.setName(filename);
    
    Map map1(10, 7);
    map1.setName("Map 1: Intro");
    MapEditor mapEditor(&map1);
    mapEditor.setStart(1, 3);
    mapEditor.setEnd(8, 3);
    mapEditor.drawSquare(0,1,4,5,WALL);
    mapEditor.drawSquare(4,0,9,6,WALL);
    mapEditor.drawSquare(4,2,4,4,EMPTY);
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
    characters.push_back(character2);
    characters.push_back(character3);



    return true;
    
}


bool Game::loadNextMap(){
    campaign.display_names();
    if (map_index >= campaign.len()){
	return false;
    } 

    map = campaign.get(0);
    map_index++;
    map.insertCharacters(characters);
    map.displayMap();
    return true;
}


void Game::initiativePhase(){
    for (Character& character : characters){
	cout << character.getName() << ": roll for initiative (press enter)";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	character.initiativeRoll = d20.Roll();
	cout << "You rolled a " << character.initiativeRoll << "!\n";
    }
}


void Game::startGameLoop(){
    initiativePhase();
}



