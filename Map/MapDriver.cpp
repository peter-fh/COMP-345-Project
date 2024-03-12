#include "MapEditorCLI.h"

using std::cout;

void testMapEditor(){
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


void testCampaign(){
    Map map0 = Map(5, 5, "0");
    Map map1 = Map(5, 5, "1");
    Map map2 = Map(5, 5, "2");

    Campaign myCampaign = Campaign();
    myCampaign.push_back(map1);
    myCampaign.push_back(map2);
    cout << myCampaign.insert(map0, 0);
    myCampaign.display_campaign();

    // Draw stuff then replace
    MapEditor mapEditor = MapEditor(myCampaign.get(1));
    mapEditor.drawSquare(1, 1, 3, 3, WALL);
    map1 = mapEditor.saveMap();
    myCampaign.replace(map1);


    myCampaign.display_campaign();
}


void testCLI(){
    MapEditorCLI editor = MapEditorCLI();
    editor.editorLoop();
}
int main(){
    //testMapEditor();
    //testCampaign();
    testCLI();
}
