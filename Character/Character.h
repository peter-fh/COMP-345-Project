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
#pragma once
#include <string>
#include <vector>
#include <cstring>
#include "../Observer/Observer.h"
#include "Strategy.h"
using std::string;

class Character : public Subject{
public:
    void Attach(Observer* observer);
    void Detach(Observer* observer);
    void Notify(string attribute, int newValue, int oldValue);

    Character(int level); // Constructor declaration
    ~Character() = default;
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
    string getName() const;
    //increase (buff and debuff)
    void increaseLevel(int levelUp);
    void increaseStrength(int strengthUp);
    void increaseDexterity(int dexterityUp);
    void increaseConstitution(int constitutionUp);
    void increaseIntelligence(int intelligenceUp);
    void increaseWisdom(int wisdomUp);
    void increaseCharisma(int charismaUp);
    void setLevel(int newLevel);
    void setHP(int newHP){
        // if(newHP<hitPoints){
        //     if(*strategy.getStrategyName() == "FriendlyStrategy"){
        //         switchToAggressive();
        //     }
        // }
        hitPoints = newHP;
        
    }
    void setStrength(int newStrength);
    void setDexterity(int newDexterity);
    void setConstitution(int newConstitution);
    void setIntelligence(int newIntelligence);
    void setWisdom(int newWisdom);
    void setCharisma(int newCharisma);
    void setName(string name);

    Character(int lvl, Strategy *initStrategy, Cell location){
        if (lvl > 0){
        level = lvl;

        strength = generateAbilityScores();
        dexterity = generateAbilityScores();
        constitution = generateAbilityScores();
        intelligence = generateAbilityScores();
        wisdom = generateAbilityScores();
        charisma = generateAbilityScores();

        strengthMod = calculateModifiers(strength);
        dexterityMod = calculateModifiers(dexterity);
        constitutionMod = calculateModifiers(constitution);
        intelligenceMod = calculateModifiers(intelligence);
        wisdomMod = calculateModifiers(wisdom);
        charismaMod = calculateModifiers(charisma);

        hitPoints = calculateHitPoints();
        armorClass = calculateArmorClass();
        attackBonus = calculateAttackBonus();
        damageBonus = calculateDamageBonus();

        this->strategy = initStrategy;
        currentLocation = location;
        }
        else{
            throw invalid_argument("Level must be positive");
        }
    }

//*************************
//FOR STRATEGY
    Character(int lvl, Strategy *initStrategy){
        if (lvl > 0){
        level = lvl;

        strength = generateAbilityScores();
        dexterity = generateAbilityScores();
        constitution = generateAbilityScores();
        intelligence = generateAbilityScores();
        wisdom = generateAbilityScores();
        charisma = generateAbilityScores();

        strengthMod = calculateModifiers(strength);
        dexterityMod = calculateModifiers(dexterity);
        constitutionMod = calculateModifiers(constitution);
        intelligenceMod = calculateModifiers(intelligence);
        wisdomMod = calculateModifiers(wisdom);
        charismaMod = calculateModifiers(charisma);

        hitPoints = calculateHitPoints();
        armorClass = calculateArmorClass();
        attackBonus = calculateAttackBonus();
        damageBonus = calculateDamageBonus();

        this->strategy = initStrategy;
        }
        else{
            throw invalid_argument("Level must be positive");
        }
    }
    void setStrategy(Strategy *setStrategy){
        strategy = setStrategy;
    }

    void performMoveAction(Character movingChar, Map currentMap){
        strategy->move(movingChar, currentMap);
    }
    void performAttackAction(Character atkingChar, Map currentMap, int dmg){
        strategy->attack(atkingChar, currentMap, dmg);
    }
    void performFreeAction(){
        strategy->freeAction();
    }
    void switchToAggressive() {
        setStrategy(new AggressorStrategy(this));
    }


    
//FOR STRATEGY^
//*************************

void setLocation(Cell destination){
    currentLocation = destination;
}
Cell getLocation(){
    return currentLocation;
}
private: // private!!!
    Strategy *strategy;
    Cell currentLocation;

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
    string name;

    int generateAbilityScores(); // generated randomly
    int calculateModifiers(int points); // default to 1
    int calculateHitPoints(); // based on constitution modifier and level
    int calculateArmorClass(); // based on dexterity modifier
    int calculateAttackBonus(); // based level and strength modifiers and dexterity modifiers
    int calculateDamageBonus(); // based on strength modifier
    // setters

    // Recalculate attributes that depend on level or modifiers
    void recalculateAttributes();
};
