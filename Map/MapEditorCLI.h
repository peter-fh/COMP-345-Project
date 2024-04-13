#pragma once
#include "MapEditor.h"

class MapEditorCLI{
    Campaign campaign;
    MapEditor mapEditor;
private:
    bool saveMap();
    bool saveMapAs();
    Map createMap();
    bool saveCampaign();
    bool loadMap();
    Map loadMapFromFile();
    bool setSquare();
    bool setCell();
    bool setStart();
    bool setEnd();
    bool moveMap();
    Map mapEditorLoop();
    void campaignEditorLoop();
public:
    MapEditorCLI();
    Campaign editorLoop(); 
};
