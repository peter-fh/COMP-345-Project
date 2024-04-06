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
#include "../Item/Item.h"
#include "../Item/Consumable.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Dice/Dice.h"
#include <iostream>
class CharUI;
using std::string;

// Forward declaration
class Map;

class Character : public Subject
{
public:
    
    Character();
    std::string status();
    std::vector<Item*> inventory;
    std::string name;
    void inventoryCheck();
    void setName(std::string name);
    std::string getName();
    int inventorySize;
    int currHP;
    void kill();
    void equip(int pos);
    void equip(Item* i);
    void pickup(Item* i);
    void drop(int pos);
    bool alive;
    Weapon* equippedWeapon;
    Armor* equippedHelmet;
    Armor* equippedChestplate;
    Armor* equippedPants;
    Armor* equippedBoots;
    void Attach(Observer *observer);
    void Detach(Observer *observer);
    void Notify(string attribute, int newValue, int oldValue);
    void Notify(string message);
    void Notify();
    void takeDamage(int damage);
    int attack(float modifier);
    int armorLevel;

    Character(int level); // Constructor declaration
    ~Character() = default;
    void printCharacter(); // Method to print character details
    string toString();
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
    int getCurrentHP();
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
    string getHelmet() const;
    string getChestplate() const;
    string getWeapon() const;
    string getBoots() const;
    string getPants() const;
    // increase (buff and debuff)
    void increaseLevel(int levelUp);
    void increaseStrength(int strengthUp);
    void increaseDexterity(int dexterityUp);
    void increaseConstitution(int constitutionUp);
    void increaseIntelligence(int intelligenceUp);
    void increaseWisdom(int wisdomUp);
    void increaseCharisma(int charismaUp);
    void setLevel(int newLevel);
    void setHP(int newHP)
    
    {
        hitPoints = newHP;
}
    void takeDmg(int hit)
    {
        if (hit < 1)
        {
            std::cout << "The hit was inneffective" << endl;
        }
        else
        {
            if (this->strategy != nullptr)
            {
                if (strategy->getStrategyName() == "FriendlyStrategy")
                {
                    switchToAggressive();
                }
            }
        }
        this->setHP(this->getHitPoints() - hit);

    }
    void setStrength(int newStrength);
    void setDexterity(int newDexterity);
    void setConstitution(int newConstitution);
    void setIntelligence(int newIntelligence);
    void setWisdom(int newWisdom);
    void setCharisma(int newCharisma);

    //*************************
    // FOR STRATEGY
    Character(Strategy *initStrategy)
    {
        this->strategy = initStrategy;
    }

    void setStrategy(Strategy *setStrategy)
    {
        strategy = setStrategy;
    }

    void performMoveAction()
    {
        strategy->move();
    }
    void performAttackAction()
    {
        strategy->attack();
    }
    void performFreeAction()
    {
        strategy->freeAction();
    }
    void switchToAggressive()
    {
        setStrategy(new AggressorStrategy());
    }

    // FOR STRATEGY^
    //*************************
    //MOVING CHARACTER
    bool moveTo(int newX, int newY, Map* currentMap);
    int getXlocation();
    int getYlocation();
    void setXLocation(int newX);
    void setYLocation(int newY);
    void setLocation(int newX, int newY);

    bool attackThere(int targetX, int targetY, Map* currentMap, int dmg); // wip
    int initiativeRoll;
    bool playing;

private: // private!!!
    int xLocation;
    int yLocation;

    Strategy *strategy;

    std::vector<Observer*> observers;
    
    int level;       // assigned at the beginning
    int hitPoints;   // based on constitution modifier and level
    int armorClass;  // based on dexterity modifier
    int attackBonus; // based level and strength/dexterity modifiers
    int damageBonus; // based on strength modifier
    int attackPerRound;
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

    int generateAbilityScores();        // generated randomly
    int calculateModifiers(int points); // default to 1
    int calculateHitPoints();           // based on constitution modifier and level
    int calculateArmorClass();          // based on dexterity modifier
    int calculateAttackBonus();         // based level and strength modifiers and dexterity modifiers
    int calculateDamageBonus();         // based on strength modifier
    // setters
    int calculateAttackPerRound();

    // Recalculate attributes that depend on level or modifiers
    void recalculateAttributes();
};
