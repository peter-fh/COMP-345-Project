#include <string>
#include <cstdlib>
#include <stdexcept>
using namespace std;

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
std::string Dice::toString(){
    return "A regular d" + to_string(sides);
}
    

}
void Dice::DiceInput() {
	Dice one;
	string parse, selection = "y";
	do {
		cout << "\nPlease Enter Your Roll in the Format xdy[z] \n \t - x is the amount of times you want to roll\n \t - y is the dice you want to roll\n \t - z is an optional addition to the sum of rolls \n";
	    getline(cin, parse);
    if (one.Parse(parse)) {
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


string Dice::toString(){
    string output = to_string(sides) + "sided dice rolled " + to_string(roll);
    return output;
}

// int main(){
//         Dice::DiceInput();
//         return 0;
// }
