#include"../Map/map.h"
#include <memory>
using namespace std;

class MapObserver : public MyObserver {
private:
    Map* map_;
public:
    MapObserver(Map* map) : map_(map) {}
    void Update() override {
        map_->displayMap();
    }
};

int main() {
    // Create a map
    Map* map = new Map(10, 10, "Example Map");
    // Create an observer for the map
    MapObserver* observer = new MapObserver(map);

    // Attach the observer to the map
    map->Attach(observer);

    // Make some changes to the map
    map->setCell(1, 1, OCCUPIED);

    // Clean up
    delete observer;
    delete map;

    return 0;
}
