#pragma once
#include <string>
#include <random>
#include "../Observer/Observer.h"
using std::string;

class Dice : public Subject{    
    /* 
    Dice Object
    default 6 sides,
    */
public:
    int sides;
    Dice();
    Dice(int diceSize);
    int Roll(int numOfRolls);
    int Roll();
    string toString();

private:
    int roll;
    std::mt19937 gen;
    std::uniform_int_distribution<> distr;
};
