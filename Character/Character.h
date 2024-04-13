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
#include "../Item/Bow.h"
#include "../Dice/Dice.h"
#include "../Item/Chest.h"
#include "../Map/Mappable.h"
#include <iostream>
class CharUI;
using std::string;

class Map;
class Corpse;

class Character : public Subject, public Mappable
{
public:
    int currXP, levelUpThreshold;
    void gainXP(int XP);
    void determineSymbol() override;
    void openChest(Chest *chest);
    void searchCorpse(Corpse *corpse);
    Character();
    std::string status();
    std::vector<Item *> inventory;
    std::string name;
    void inventoryCheck();
    void setName(std::string name);
    std::string getName();
    int inventorySize;
    int currHP;
    void kill();
    void equip(int pos);
    void equip(Item *i);
    void pickup(Item *i);
    void drop(int pos);
    int bowAttack(float modi);
    bool alive;
    Weapon *equippedWeapon;
    Armor *equippedHelmet;
    Armor *equippedChestplate;
    Armor *equippedPants;
    Armor *equippedBoots;
    Bow *equippedBow;
    void Attach(Observer *observer) override;
    void Detach(Observer *observer) override;
    void Notify(string attribute, int newValue, int oldValue);
    void Notify(string message);
    void Notify() override;
    void takeDamage(int damage);
    int attack(float modifier);
    int armorLevel;

    Character(int level); // Constructor declaration
    ~Character() = default;
    void printCharacter(); // Method to print character details
    string toString();
    // getters
    int getLevel();
    int getHitPoints();
    int getCurrentHP();
    int getArmorClass();
    int getAttackBonus();
    // getters for abilities
    int getStrength();
    // getters for equipment
    string getHelmet() const;
    string getChestplate() const;
    string getWeapon() const;
    string getBoots() const;
    string getPants() const;
    // increase (buff and debuff)
    void heal();
    void setHP(int newHP)
    {
        hitPoints = newHP;
    }
    void setCurrentHP(int newHP);

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
    void setStrength(int newStrength)
    {
        strength = newStrength;
    }

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
    void setLevel(int passedlevel);

    // FOR STRATEGY^
    //*************************
    // MOVING CHARACTER
    bool moveTo(int newX, int newY, Map *currentMap);

    int initiativeRoll;

    void saveCharacter();
    static Character loadCharacter(string filename);

private: // private!!!
    Strategy *strategy;

    std::vector<Observer *> observers;

    int level;       // assigned at the beginning
    int hitPoints;   // based on constitution modifier and level
    int armorClass;  // based on dexterity modifier
    int attackBonus; // based level and strength/dexterity modifiers
    int damageBonus; // based on strength modifier
    int attackPerRound;
    // ability score
    int strength;
    // ability modifier

    int calculateAttackPerRound();
};
