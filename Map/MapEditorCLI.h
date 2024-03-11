#include "MapEditor.h"

class MapEditorCLI{
    Campaign campaign;
    MapEditor mapEditor;
private:
    bool setSquare(int x1, int y1, int x2, int y2, int type);
    bool setCell(int x, int y, int type);
    bool setStart(int x, int y);
    bool setEnd(int x, int y);
public:
    MapEditorCLI();
    MapEditorCLI(MapEditor in_map_editor);
    MapEditorCLI(Campaign in_campaign);
    Campaign editorLoop(); 
};
