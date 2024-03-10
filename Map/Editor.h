#include "Campaign.h"


class Editor {
private:
    Map *map;
    Campaign campaign;
public:
    bool drawSquare(int x1, int y1, int x2, int y2, int type);
    bool drawCell(int x, int y, int type);
    bool beginEditing(string name);
    bool beginEditing(int index);
    bool createMap(string name, int width, int height);
    bool createMap(string name, int width, int height, int index);

};
