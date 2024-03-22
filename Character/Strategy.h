#pragma once
#include "../Map/map.h"
#include "../Character/Character.h"
#include <iostream>

using namespace std;

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void move(Character movingChar, Map currentMap, Cell destination) = 0;
    virtual void attack(Cell toAttack) = 0;
    virtual void freeAction() = 0;
};

class HumanPlayerStrategy : public Strategy {
    public:
        void move(Character movingChar, Map currentMap, Cell destination) override{
            Cell currentCell = movingChar.getLocation();
            currentMap.setCell(destination.x,destination.y,OCCUPIED,movingChar);
            movingChar.setLocation(currentMap.getCell(destination.x,destination.y));
            currentMap.setCell(currentCell.x,currentCell.y,EMPTY);
        }
        void attack(Cell toAttack) override{
        }
        void freeAction() override{

        }
};

// class AggressorStrategy : public Strategy {
//     public:
//         void move(Character movingChar, Map currentMap, Cell destination) override{

//         }
//         void attack(Cell toAttack) override{

//         }
//         void freeAction() override{

//         }
// };

// class FriendlyStrategy : public Strategy {
//     public:
//         void move(Character movingChar, Map currentMap, Cell destination) override{

//         }
//         void attack(Cell toAttack) override{

//         }
//         void freeAction() override{

//         }
// };