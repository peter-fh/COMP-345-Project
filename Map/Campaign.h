#include <list>
#include "Map.h"
#include <optional>

class Campaign {
    std::list<Map> maps;
public:
    Campaign();
    Map get(int index);
    void set(Map map, int index);
    void push_back(Map map);
    void display_names();
};


