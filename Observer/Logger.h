#pragma once
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
    ~Logger();
    void Update(Subject* subject);
    void attachMap(Map* map);
    void attachCharacter(Character* character);
    void attachDice(Dice* dice);
    void Update();
    void logMap();
    void logCharacter();
    void logDice();

private:

    Sources sources;
    Map* map;
    Character* character;
    Dice* dice;
    string logFile;
};
