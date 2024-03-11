#include "Campaign.h"


Map Campaign::get(int index){
    if (index > maps.size())
	return  maps.back();
    
    std::list<Map>::iterator it = maps.begin();
    advance(it, index);
    return *it;

}


void Campaign::set(Map map, int index){
    if (index > maps.size()){
	push_back(map);
	return;
    }

    std::list<Map>::iterator it = maps.begin();
    advance(it, index);
    *it = map;
    
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


    
