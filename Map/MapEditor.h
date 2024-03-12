#include "Campaign.h"



class MapEditor{
private:
    Map editedMap;
public:
    MapEditor();
    MapEditor(Map inp_map);
    bool drawSquare(int x1, int y1, int x2, int y2, int type);
    bool drawCell(int x, int y, int type);
    bool setStart(int x, int y);
    bool setEnd(int x, int y);
    Map saveMap();

};



