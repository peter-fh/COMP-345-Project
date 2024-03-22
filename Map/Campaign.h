#pragma once
#include <list>
#include "Map.h"
#include <optional>

class Campaign {
    std::list<Map> maps;
    string name;
public:
    Campaign();
    string getName();
    void setName(string inp_name);
    Map* get(int index);
    Map* get(string name);
    bool remove(Map map);
    bool replace(Map map);
    bool set(Map map, int index);
    bool insert(Map map, int index);
    bool swap(string map1, string map2);
    void push_back(Map map);
    void display_campaign();
    void display_names();
};


