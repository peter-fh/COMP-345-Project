#include "MapEditor.h"

class MapEditorCLI{
    Campaign campaign;
    MapEditor mapEditor;
private:
    bool saveMap();
    bool saveMapAs();
    Map createMap();
    bool loadMap();
    bool setSquare();
    bool setCell();
    bool setStart();
    bool setEnd();
    bool moveMap();
    Map mapEditorLoop();
public:
    MapEditorCLI();
    Campaign editorLoop(); 
};
