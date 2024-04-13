#include <fstream>
#include <sstream>
#include "Campaign.h"


Campaign::Campaign() {
    Map map(5, 5);
}


Map* Campaign::get(int index){
    if (index > maps.size())
	return nullptr; 
    std::list<Map>::iterator it = maps.begin();
    advance(it, index);
    return &*it;

}


Map* Campaign::get(string name){
    for (std::list<Map>::iterator it = maps.begin(); it != maps.end(); ++it){
	if (it->getName() == name){
	    return &*it;
	}
    }

    return nullptr;
}


bool Campaign::swap(string map1, string map2){
    bool foundFirst = false;
    bool foundSecond = false;
    std::list<Map>::iterator map1_it;
    std::list<Map>::iterator map2_it;
    for (map1_it = maps.begin(); map1_it != maps.end(); ++map1_it){
	if (map1_it->getName() == map1){
	    foundFirst = true;
	    break;
	}
    }

    for (map2_it = maps.begin(); map2_it != maps.end(); ++map2_it){
	if (map2_it->getName() == map2){
	    foundSecond = true;
	    break;
	}
    }

    if (foundFirst && foundSecond){
	std::swap(*map1_it, *map2_it);
	return true;
    }

    return false;


}

bool Campaign::insert(Map map, int index){
    if (index > maps.size()){
	return false;
    }

    std::list<Map>::iterator it = maps.begin();
    advance(it, index);
    maps.insert(it, map);
    return true;
}


bool Campaign::set(Map map, int index){
    if (index > maps.size()){
	return false;
    }

    std::list<Map>::iterator it = maps.begin();
    advance(it, index);
    *it = map;
    return true;
    
}


void Campaign::push_back(Map map){
    maps.push_back(map);
}


int Campaign::len(){
	return maps.size();
}

void Campaign::display_names(){
    std::cout << "Campaign Maps:\n";
    int i=0;
    for(std::list<Map>::iterator it = maps.begin(); it != maps.end(); ++it){
	std::cout << i << ": "<< it->getName() << "\n";
	++i;
    }
}


void Campaign::display_campaign(){
    std::cout << "Campaign Maps:\n";
    for(std::list<Map>::iterator it = maps.begin(); it != maps.end(); ++it){
	std::cout << "\n"<<it->getName();
	it->displayMap();
    std::cout << "\n";

    }
}


bool Campaign::replace(Map map){
    for (std::list<Map>::iterator it = maps.begin(); it != maps.end(); ++it){
	if (it->getName() == map.getName()){
	    it = maps.erase(it);
	    maps.insert(it, map);
	    return true;
	}
    }

    return false;
}


bool Campaign::remove(Map map){
    for (std::list<Map>::iterator it = maps.begin(); it != maps.end(); ++it){
	if (it->getName() == map.getName()){
	    maps.erase(it);
	    return true;
	}
    }

    return false;
}

string Campaign::getName() {return name;}

void Campaign::setName(string inp_name) {name = inp_name;}



void Campaign::saveCampaign(){
    std::ofstream file(getName()+ ".txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file for saving." << std::endl;
        return;
    }

    int i=0;
    for(std::list<Map>::iterator it = maps.begin(); it != maps.end(); ++it){
        it->saveMap();
        file << i << ":"<< it->getName() << "\n";
        ++i;
    }    
    file.close();
}

Campaign Campaign::loadCampaign(string filename){
    Campaign campaign;
    campaign.setName(filename.substr(0, filename.size() - 4));
    std::ifstream file(filename);
    std::string line;
    
    if (file.is_open()) {
        while (getline(file, line)) {
            std::istringstream iss(line);
            std::string index, mapName;
            if (getline(iss, index, ':') && getline(iss, mapName)) {
                std::string filename = mapName + ".txt"; // Create filename
                campaign.push_back(Map::loadMap(filename)); // Load the map
            }
        }
        file.close();
    } else {
        std::cout << "Failed to open file." << std::endl;
    }
    return campaign;
}