/**
 * @file main.cpp
 * @brief Driver file
 *
 * This file is the driver, it initializes all the objects: Character, Dice, Map and Items with Item container
 *
 * @author Eric Liu
 * @date 2024-02-25
 */
#include "Character.h"
#include "Dice.h"
#include "map.h"
// #include "Item.h"
#include <iostream>
using namespace std;

// Main function to initialize all objects
int main() {
    srand(time(0)); // create random seed
    // initializing a fighter Character
    Character fighter(1);
    fighter.printCharacter();

    // initializing a dice
    Dice::DiceInput();

    // inializing a map
    Map map (20, 20, Cell(0, 0), Cell(19, 19));
    
    for (int y = 0; y < map.height; y++)
	map.setCell(Cell(14, y), WALL);

    map.setCell(Cell(14, 17), EMPTY);
    map.displayMap();
    cout << map.validate() << "\n";

    // inializing items with item container
    
    return 0;
}