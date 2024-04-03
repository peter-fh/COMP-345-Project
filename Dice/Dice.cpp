#include <string>
#include <cstdlib>
#include <stdexcept>
using namespace std;
#include "Dice.h"


//Jackson Abbott

Dice::Dice() : Dice(6){}

Dice::Dice(int diceSides){
    std::random_device rd;
    gen = std::mt19937(rd());
    distr = std::uniform_int_distribution<>(1, diceSides);
}

int Dice::Roll(int numOfRolls){
    int sum = 0;
    int curr = 0;
    for(int i = 0; i < numOfRolls; i++){
        curr = distr(gen);
	    cout << "Roll " << (i+1) << " is " << curr << "\n";
	    sum = sum + curr;
    }
    cout << "The sum of your rolls was: " << sum;
    return sum;
    }

int Dice::Roll(){
    roll = distr(gen);
    Notify();
    return roll;
    }

string Dice::toString(){
    string output = to_string(sides) + "sided dice rolled " + to_string(roll);
    return output;
}

// int main(){
//         Dice::DiceInput();
//         return 0;
// }
