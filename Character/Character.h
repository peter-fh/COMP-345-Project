/**
 * @file Character.h
 * @brief Declaration of the Character class for a DND game.
 *
 * This file declares the Character class, including constructors, methods for equipping gear,
 * getters for character attributes and equipment, and methods for increasing character abilities.
 * The class represents a character in a DND game, encapsulating attributes such as
 * strength, dexterity, intelligence, as well as character equipment like armor and weapons.
 * 
 * Design Description:
 * - The Character class encapsulates a character's attributes, equipment, and actions like equipping gear and stat increases.
 * - Attributes affect combat outcomes, simulated through methods calculating bonuses and hit points.
 * 
 * Libraries Used:
 * - <string> for representing character names and equipment. Chosen for comprehensive support for string operations.
 * 
 * @author Eric Liu
 * @date 2024-02-25
 */
#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <vector>
#include "../Subject/Subject.h"
using std::string;

class Character : public Subject{
public:
    Character(int level); // Constructor declaration
    void printCharacter(); // Method to print character details
    // equip gear
    void equipArmor(string newArmor);
    void equipShield(string newShield);
    void equipWeapon(string newWeapon);
    void equipBoots(string newBoots);
    void equipRing(string newRing);
    void equipHelmet(string newHelmet);
    // getters
    int getLevel() const;
    int getHitPoints() const;
    int getArmorClass() const;
    int getAttackBonus() const;
    int getDamageBonus() const;
    // getters for abilities
    int getStrength() const;
    int getDexterity() const;
    int getConstitution() const;
    int getIntelligence() const;
    int getWisdom() const;
    int getCharisma() const;
    // getters for abilitiy modifiers
    int getStrengthMod() const;
    int getDexterityMod() const;
    int getConstitutionMod() const;
    int getIntelligenceMod() const;
    int getWisdomMod() const;
    int getCharismaMod() const;
    // getters for equipment
    string getArmor() const;
    string getShield() const;
    string getWeapon() const;
    string getBoots() const;
    string getRing() const;
    string getHelmet() const;
    //increase (buff and debuff)
    void increaseLevel(int levelUp);
    void increaseStrength(int strengthUp);
    void increaseDexterity(int dexterityUp);
    void increaseConstitution(int constitutionUp);
    void increaseIntelligence(int intelligenceUp);
    void increaseWisdom(int wisdomUp);
    void increaseCharisma(int charismaUp);

private: // private!!!
    vector<Observer*> observers;
    int level; // assigned at the beginning
    int hitPoints; // based on constitution modifier and level
    int armorClass; // based on dexterity modifier
    int attackBonus; // based level and strength/dexterity modifiers
    int damageBonus; //based on strength modifier
    // ability score
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
    // ability modifier
    int strengthMod;
    int dexterityMod;
    int constitutionMod;
    int intelligenceMod;
    int wisdomMod;
    int charismaMod;
    // equipment
    string armor;
    string shield;
    string weapon;
    string boots;
    string ring;
    string helmet;

    int generateAbilityScores(); // generated randomly
    int calculateModifiers(int points); // default to 1
    int calculateHitPoints(); // based on constitution modifier and level
    int calculateArmorClass(); // based on dexterity modifier
    int calculateAttackBonus(); // based level and strength modifiers and dexterity modifiers
    int calculateDamageBonus(); // based on strength modifier
    // setters
    void setLevel(int newLevel);
    void setStrength(int newStrength);
    void setDexterity(int newDexterity);
    void setConstitution(int newConstitution);
    void setIntelligence(int newIntelligence);
    void setWisdom(int newWisdom);
    void setCharisma(int newCharisma);
    // Recalculate attributes that depend on level or modifiers
    void recalculateAttributes();
};
#endif // CHARACTER_H
