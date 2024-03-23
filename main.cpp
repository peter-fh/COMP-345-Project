#include "Map/MapEditorCLI.h"
#include "Character/CharUI.h"
#include "Item/Item.cpp"
#include "Dice/Dice.h"
#include "Observer/Logger.h"


int main(){
    Map map(5, 5);
    Logger logger;
    map.Attach(&logger);
    logger.attachMap(&map);
    
    map.setStart(0, 4);
    map.setEnd(4, 0);
}
