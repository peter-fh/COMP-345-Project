#include <string>

/* const int EMPTY = 0;
const int WALL = 1;
const int OCCUPIED = 2;
const int START = 3;
const int END = 4; */

struct Textures{
    std::string wall[6] = {
	"##########",
	"# # # # ##",
	"## # # # #",
	"# # # # ##",
	"## # # # #",
	"##########"
    };

    /* std::string wall[6] = {
	" # # # # #",
	"# # # # # ",
	" # # # # #",
	"# # # # # ",
	" # # # # #",
	"# # # # # "
    };*/

    /*std::string empty[6] = {
	"          ",
	"    __    ",
	"   |  |   ",
	"   |__|   ",
	"          ",
	"          "
    };*/
    /* std::string empty[6] = {
	"          ",
	" |------| ",
	" |      | ",
	" |      | ",
	" |------| ",
	"          "
    }; */

    std::string empty[6] = {
	" ________ ",
	"|        |",
	"|        |",
	"|        |",
	"|________|",
	"          "
    }; 
    std::string start[6] = {
	" |====|   ",
	" |IN  |   ",
	" |    |   ",
	" |  o |   ",
	" |    |   ",
	" |====|   "
    };
    std::string end [6] = {
	"   |====| ",
	"   | OUT| ",
	"   |    | ",
	"   | o  | ",
	"   |    | ",
	"   |====| "
    };

    std::string character[6] = {
	"          ",
	"   O      ",
	"  /|\\     ",
	"  / \\     ",
	"          ",
	"          ",
    };
    std::string enemy[6] = {
	"          ",
	"          ",
	"      X   ",
	"     /|\\  ",
	"     / \\  ",
	"          ",
    };

    std::string bag[6] = {
	"     ___  ",
	"    /   \\ ",
	"    | $ | ",
	"    \\___/ ",
	"          ",
	"          ",
    };
};
