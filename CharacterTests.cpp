/**
 * @file CharacterTests.cpp
 * @brief Unit tests for the Character class in a role-playing game.
 *
 * This file includes tests for the Character class, ensuring the correct behavior of its constructor,
 * level management, attribute modification methods, and gear equipment functionality. It uses assertions
 * to validate the initial state of a character, level progression, attribute increases, and the successful
 * equipment of gear items. The output of each test case is directed to standard output, indicating success.
 *
 * @author Eric Liu
 * @date 2024-02-25
 */
#include "Character.h"
#include <iostream>
#include <cassert>
using namespace std;

// Test constructor and level initialization
void testConstructor() {
    Character testCharacter(1);
    assert(testCharacter.getLevel() == 1);
    assert(testCharacter.getHitPoints() > 0);

    assert(testCharacter.getStrength() > 2);
    assert(testCharacter.getDexterity() > 2);
    assert(testCharacter.getConstitution() > 2);
    assert(testCharacter.getIntelligence() > 2);
    assert(testCharacter.getWisdom() > 2);
    assert(testCharacter.getCharisma() > 2);
    cout << "testConstructor passed\n";
}

// Test increasing level
void testIncreaseLevel() {
    Character testCharacter(1);
    testCharacter.increaseLevel(1);
    assert(testCharacter.getLevel() == 2);
    cout << "testIncreaseLevel passed\n";
}

// Test strength attribute and modifier
void testStrengthAttribute() {
    Character testCharacter(1);
    int initialStrength = testCharacter.getStrength();
    testCharacter.increaseStrength(5);
    assert(testCharacter.getStrength() == initialStrength + 5);
    cout << "testStrengthAttribute passed\n";
}

// Test armor equipment
void testEquipArmor() {
    Character testCharacter(1);
    testCharacter.equipArmor("Chain Mail");
    assert(testCharacter.getArmor() == "Chain Mail");
    cout << "testEquipArmor passed\n";
}

void testPrint() {
    Character testCharacter(1);
    testCharacter.printCharacter();
    cout << "testPrint passed\n";
}

// // Main function to run all tests
// int main() {
//     srand(time(0)); // create random seed
//     testConstructor();
//     testIncreaseLevel();
//     testStrengthAttribute();
//     testEquipArmor();
//     testPrint();

//     cout << "All tests passed!\n";
//     return 0;
// }