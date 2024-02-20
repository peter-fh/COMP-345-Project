#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
using std::string;


class Character {
public:
    Character(int level); // Constructor declaration
    void printCharacter(); // Method to print character details

private:
    int level;
    int hitPoints;
    int armorClass;
    int attackBonus;
    int damageBonus;
    // ability and their modifiers in an array of size 2
    int strength[2];
    int dexterity[2];
    int constitution[2];
    int intelligence[2];
    int wisdom[2];
    int charisma[2];
    // equipment
    string armor;
    string shield;
    string weapon;
    string boots;
    string ring;
    string helmet;


    void generateAbilityScores(); // generated randomly
    void calculateModifiers(); // 
    void calculateHitPoints(); // based on constitution modifier and level
    void calculateArmorClass(); // based on dexterity modifier
    void calculateAttackBonus(); // based level and strength modifiers and dexterity modifiers
    void calculateDamageBonus(); // based on strength modifier

};
#endif // CHARACTER_H
