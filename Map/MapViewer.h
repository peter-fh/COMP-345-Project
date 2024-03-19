#include "MapEditor.h"

class MapViewer : Observer {
public:
    MapViewer();
    void Update(Map *updatedMap);
private:
    Map* map;
};

