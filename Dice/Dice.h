#pragma once
#include <string>

#include "../Observer/Observer.h"
using std::string;

class Dice : public Subject{    
    /* 
    Dice Object
    Can be initialized with Dice(sizeOfDice), default is 6, each roll function prints the value into console and then returns the sum
    Roll() returns a single roll of the initialized dice
    Roll(int numOfRolls) will  print each roll individually as well as the sum of all the rolls, then return the sum
    Roll(int numOfRolls, int diceSize) will roll a dice of indicated size an indicated number of times)
    Roll(int numOfRolls, int diceSize, int plus) does the same but ads the sum to the final roll
    */
public:
    int sides;
    Dice();
    Dice(int diceSize);
    bool Valid(int d);
    int Roll(int numOfRolls,int DiceSize,int plus);
    int Roll(int numOfRolls, int DiceSize);
    int Roll(int numOfRolls);
    int Roll();
    bool Parse(string s);
    static void DiceInput();
    string toString();

private:
    int roll;
};
