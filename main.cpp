/**
 * @file main.cpp
 * @brief Driver file for initializing game components.
 *
 * This driver file serves as the entry point for a simple game, initializing objects
 * for characters, dice, maps, and items within an item container. It demonstrates
 * the creation and interaction of these objects, setting up a basic game environment.
 * The file showcases object initialization, random seed generation for dice rolling,
 * map setup with obstacles, and displaying item enchantments.
 *
 * Usage:
 * - Character initialization and display.
 * - Dice rolling mechanism.
 * - Map generation with obstacles and validation.
 * - Item enchantment display.
 *
 * @author Eric Liu
 * @date 2024-02-25
 */
#include "Character.h"
#include "Dice.h"
#include "map.h"
#include "Item.cpp"
#include <iostream>
using namespace std;

// Main function to initialize all objects
int main() {
    srand(time(0)); // create random seed

    // Code to initialize and demonstrate the functionality of game components.

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

    // inializing items
    Helmet helmet1;
    Armor armor1;
    Shield shield1;
    Ring ring1;
    Belt belt1;
    Boots boots1;
    Weapon weapon1;
    cout << helmet1.getType() << " gives:" << helmet1.getEnchantment() << endl;
    cout << armor1.getType() << " gives:" << armor1.getEnchantment() << endl;
    cout << shield1.getType() << " gives:" << shield1.getEnchantment() << endl;
    cout << ring1.getType() << " gives:" << ring1.getEnchantment() << endl;
    cout << belt1.getType() << " gives:" << belt1.getEnchantment() << endl;
    cout << boots1.getType() << " gives:" << boots1.getEnchantment() << endl;
    cout << weapon1.getType() << " gives:" << weapon1.getEnchantment() << endl;
    return 0;
}