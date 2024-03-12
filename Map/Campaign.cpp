#include "Campaign.h"


Campaign::Campaign() {}


Map* Campaign::get(int index){
    if (index > maps.size())
	return nullptr; 
    std::list<Map>::iterator it = maps.begin();
    advance(it, index);
    return &*it;

}


Map* Campaign::get(string name){
    for (std::list<Map>::iterator it = maps.begin(); it != maps.end(); ++it){
	std::cout << "Looping through maps";
	if (it->getName() == name){
	    return &*it;
	}
    }

    return nullptr;
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
	std::cout << it->getName();
	it->displayMap();
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
