#include "MapEditor.h"
using std::cout;

int main(){
    Map map = Map(10, 10, "");
    map.setStart(0, 0);
    map.setEnd(7, 7);

    MapEditor mapEditor = MapEditor(map);    

    bool squareSuccess = mapEditor.drawSquare(1, 1, 8, 8, WALL);
    map.displayMap();
    map = mapEditor.saveMap();

    map.displayMap();
    bool valid_map = map.validate();
    if (valid_map)
	cout << "valid map";
    else 
	cout << "invalid map";
    cout << "\n";
}
