#include "Dice.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
using namespace std;

//Jackson Abbott

        Dice::Dice(){
            sides = 6;
        }
        Dice::Dice(int diceSides){
            if (Valid(diceSides)) sides = diceSides;
            else sides = 0;
        }
        bool Dice::Valid(int d){
            //checks to see if the dice entered was one of the valid ones. split only to test calling functions from functions
            int valid[] = {4, 6, 8, 10, 12, 20, 100};
            for (int i= 0; i<7; i++){
                if(valid[i] == d){
                    return true;
                }
            }
            return false;
        }
        int Dice::Roll(int numOfRolls, int diceSize, int plus){
            //callouts for function
            int curr = 0;
            int sum = 0;
            for(int i = 0; i < numOfRolls; i++){
                    curr = rand() % diceSize + 1;
                    sum = sum + curr;
                    cout << "Roll " << (i+1) << " is " << curr << "\n";
                }
                
                cout << "The sum of your rolls was: " << sum + plus;
                return sum + plus;
        }
        int Dice::Roll(int numOfRolls, int diceSize){
            int sum = 0;
            int curr = 0;
            for(int i = 0; i < numOfRolls; i++){
                curr = rand() % diceSize + 1;
                cout << "Roll " << (i+1) << " is " << curr << "\n";
                sum = sum + curr;
            }
            cout << "The sum of your rolls was: " << sum;
            return sum;
            }

        int Dice::Roll(int numOfRolls){
            int sum = 0;
            int curr = 0;
            for(int i = 0; i < numOfRolls; i++){
                curr = rand() % sides + 1;
                cout << "Roll " << (i+1) << " is " << curr << "\n";
                sum = sum + curr;
            }
            cout << "The sum of your rolls was: " << sum;
            return sum;
            }

        int Dice::Roll(){

            int value = (rand() % sides + 1);
            cout << "Your roll was: " << value;
            return value;
            }
        
        bool Dice::Parse(string s){
            //Parses string and calls function with variables
            int n, b, plus, d = 0;
            int dLoc = s.find('d');
            int oB = s.find('[');
            int cB = s.find(']');

            if (dLoc == -1) return false;

            string first = s.substr(0, dLoc);
            string second;
            string third = "";
            if (oB != string::npos && cB!= string::npos) {
                //verifies that all elements were in the string
                second = s.substr(dLoc + 1, oB - dLoc - 1);
                third = s.substr(oB + 1, cB - oB - 1);
            } else {
                second = s.substr(dLoc + 1);
            }
            try{
                n = stoi(first);
                b = stoi(second);
                if (!Valid(b)){
                    return false;
                }
                sides = b;
                if (!third.empty()) {
                    plus = stoi(third);
            }
            }catch(exception err){
                return false;
            }
            Roll(n, b, plus);

            return true;

            

        }
        static void Dice::DiceInput() {
                Dice one;
                string parse, selection = "y";
                do {
                        cout << "\nPlease Enter Your Roll in the Format xdy[z] \n \t - x is the amount of times you want to roll\n \t - y is the dice you want to roll\n \t - z is an optional addition to the sum of rolls \n";
                    getline(cin, parse);
            if (Parse(parse)) {
                cout << "\nWould you like to roll again? (y/n): ";
                getline(cin, selection);
            } else {
                cout << "Invalid selection, please type y if you would like to try and roll again? (y/n): ";
                getline(cin, selection);
            }

            while (selection[0] != 'y' && selection[0] != 'Y' && selection[0] != 'n' && selection[0] != 'N') {
                cout << "Invalid entry, would you like to roll again? (y/n): ";
                getline(cin, selection);
            }
        } while (selection == "Y" || selection == "y");
    }
};


int main(){
        Dice::DiceInput();
        return 0;
}
