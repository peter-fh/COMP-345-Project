#include <fstream>
#include "Observer.h"
#include "../Dice/Dice.h"

#ifndef MAP_H
#define MAP_H
#include "../Map/Map.h"
#endif


struct Sources {
    bool gameLoop;
    bool map;
    bool character;
    bool dice;
    
    Sources() : gameLoop(false), map(false), character(false), dice(false) {}
};


class Logger : public Observer {
public:
    
    Logger();
    Logger(std::string file_name);
    void Update(Subject* subject);
    void Update();
    void logMap();
    void logCharacter();
    void logDice();

private:

    Sources sources;
    Map* map;
    Character* character;
    Dice* dice;
    ofstream logFile;
};
