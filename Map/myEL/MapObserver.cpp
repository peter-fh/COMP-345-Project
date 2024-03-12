#include"../map.h"
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



// to compile this code
// g++ -o mapO Map/Map.cpp Map/myEL/MySubject.cpp Map/myEL/MyObserver.cpp Map/myEL/MapObserver.cpp

int main() {
    cout<<"hello";
    // Create a map
    int mapSize = 10;

    Map* map = new Map(mapSize);
    // Create an observer for the map
    MapObserver* observer = new MapObserver(map);
    // Attach the observer to the map
    map->Attach(observer);

    // make some changes to the map
    map->setCell(0, 0, START);
    map->setCell(mapSize-1, mapSize-1, END);
    // set some walls
    for(int i=0;i<mapSize;i++){
        for(int j=0;j<mapSize;j++){
            if(i==j){
                map->setCell(i, j, WALL);
            }        
        }
    }
    // make things occupied
    for(int i=0;i<mapSize;i=i+2){
        for(int j=0;j<mapSize;j=j+2){
            if(i==mapSize-j){
                map->setCell(i,j, OCCUPIED);
            }        
        }
    }
    
    

    // Clean up
    delete observer;
    delete map;

    return 0;
}
