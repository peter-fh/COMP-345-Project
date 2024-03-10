#include "map.h"
using std::cout;

int main(){
    Map map = Map(10, 10);
    map.setStart(2, 2);
    map.setEnd(7, 7);
    for (int y=0; y < 10; y++){
	map.setCell(4, y, WALL);
    }

    map.displayMap();
    bool valid_map = map.validate();
    if (valid_map)
	cout << "valid map";
    else 
	cout << "invalid map";
    cout << "\n";
}
