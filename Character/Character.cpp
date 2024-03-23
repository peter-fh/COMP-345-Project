/**
 * @file Character.cpp
 * @brief Implementation of the Character class for a role-playing game.
 *
 * Defines the Character class constructor, ability score generation, modifiers calculation, and character
 * attribute recalculations. It also includes methods for leveling up, increasing abilities, equipping gear,
 * and printing character details. The implementation utilizes random number generation for simulating
 * ability score rolls and includes error handling for invalid level inputs.
 *
 * @author Eric Liu
 * @date 2024-02-25
 */
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime>   // For std::time()
#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>
#include <math.h>
#include "Character.h"
#include "../Observer/Observer.h"

using namespace std;


Character::Character(){}

void CharacterWeapon::equip(Item* i){
    Weapon* W = dynamic_cast<Weapon*>(i);
    if (equippedWeapon = nullptr){
        Notify("Equipped " + W->getItemName() + " (" + std::to_string(W->getDamage()) + ")");
        equippedWeapon = W;
    }
    else{
        unequip(equippedWeapon);
        Notify("Equipped " + W->getItemName() + " (" + std::to_string(W->getDamage()) + ")");
        equippedWeapon = W;
    }
}

void CharacterWeapon::unequip(Item* i){
    Notify("Unequipped " + equippedWeapon->getItemName() + " (" + std::to_string(equippedWeapon->getDamage()) + ")");
    equippedWeapon = nullptr;
}

void CharacterArmor::equip(Item* i){
    Armor* A = dynamic_cast<Armor*>(i);
    if (A-> getType() == "Boots"){
        if (equippedBoots == nullptr){
            Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
            character->armorLevel += A->getDefence();
            equippedBoots = A;
        }
        else{
            unequip(equippedBoots);
            Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
            character->armorLevel += A->getDefence();
            equippedBoots = A;
        }}

    if (A-> getType() == "Pants"){
        if (equippedPants == nullptr){
            Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
            character->armorLevel += A->getDefence();
            equippedPants = A;
        }
        else{
            Notify("Swapped pants");
            unequip(equippedPants);
            Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
            character->armorLevel += A->getDefence();
            equippedPants = A;
        }}
    if (A-> getType() == "Chestplate"){
        if (equippedChestpiece == nullptr){
            Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
            character->armorLevel += A->getDefence();
            equippedChestpiece = A;
        }
        else{
            Notify("Swapped chestplate");
            unequip(equippedChestpiece);
            Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
            character->armorLevel += A->getDefence();
            equippedChestpiece = A;
        }}
    if (A-> getType() == "Helmet"){
        if (equippedHelmet == nullptr){
            Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
            character->armorLevel += A->getDefence();
            equippedHelmet = A;
        }
        else{
            Notify("Swapped helmet");
            unequip(equippedHelmet);
            Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
            character->armorLevel += A->getDefence();
            equippedHelmet = A;
        }}
}


void CharacterArmor::takeDamage(int dmg){
    if ((armorLevel - dmg) <= 0){
        return;
    }
    character->currHP =+ armorLevel-dmg;
}

int CharacterWeapon::attack(){
    return character->getStrength() + equippedWeapon->getDamage();
}

void CharacterArmor::unequip(Item* i){
    Armor* A = dynamic_cast<Armor*>(i);
    if (A-> getType() == "Helmet"){
        Notify("Unequipped " + equippedHelmet->getItemName() + " (" + std::to_string(equippedHelmet->getDefence()) + ")");
        character->armorLevel -= equippedHelmet->getDefence();
        equippedHelmet = nullptr;
    }
    if (A-> getType() == "Chestplate"){
        Notify("Unequipped " + equippedChestpiece->getItemName() + " (" + std::to_string(equippedChestpiece->getDefence()) + ")");
        character->armorLevel -= equippedChestpiece->getDefence();
        equippedChestpiece = nullptr;
    }
    if (A-> getType() == "Pants"){
        Notify("Unequipped " + equippedPants->getItemName() + " (" + std::to_string(equippedPants->getDefence()) + ")");
        character->armorLevel -= equippedPants->getDefence();
        equippedPants = nullptr;
    }
    if (A-> getType() == "Boots"){
        Notify("Unequipped " + equippedBoots->getItemName() + " (" + std::to_string(equippedBoots->getDefence()) + ")");
        character->armorLevel -= equippedBoots->getDefence();
        equippedBoots = nullptr;
    }
}



void Character::takeDamage(int damage){
    currHP -= damage;
    if (currHP <= 0){
        kill();
        //reload save logic?
        //~Character();
    }
}

std::string Character::getName(){return name;}

void Character::kill(){
    Notify("Your character has taken too much damage and perished");
    alive = false;
    Corpse characterCorpse(this);
    //Probably remove observers here
}


void Character::pickup(Item* i){
    if (inventory.size() >= inventorySize) Notify("Cannot pickup " + i->getItemName() + " inventory full.");
    else{
        Notify("Picked up " + i->getItemName() + "!");
        inventory.push_back(i);
        i->pickup();
        //inventorySize++;
    }
}


void Character::drop(int pos){
    Item* i = inventory[pos];
    i->drop();
    inventory.erase(inventory.begin() + pos);
}


int Character::attack(){
    return strength + equippedWeapon->getDamage();
    //use a damage modifier based on dice in the future
}


void Character::equip(Item* i){
    Consumable* C = dynamic_cast<Consumable*>(i);
    if (C) {
        currHP += C->getValue();
        delete C;
        return;
    }
    Weapon* W = dynamic_cast<Weapon*>(i);
    if (W) {
         if (equippedWeapon == nullptr){
            Notify("Equipped " + W->getItemName() + " (" + std::to_string(W->getDamage()) + ")");
            equippedWeapon = W;
            W->equip();
            return;
         }
         else{
            Notify("Unequipped " + equippedWeapon->getItemName() + " (" + std::to_string(equippedWeapon->getDamage()) + ") Equipped " + W->getItemName() + " (" + std::to_string(W->getDamage()) + ")");
            equippedWeapon->unEquip();
            equippedWeapon = W;
            W->equip();
            return;
         }
    }
    Armor* A = dynamic_cast<Armor*>(i);
    if (A){
        if (A-> getType() == "Chestplate"){
            if (equippedChestplate == nullptr){
                Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                equippedChestplate = A;
                A->equip();
                armorLevel += A->getDefence();
                return;
            }
            else{
                Notify("Unequipped " + equippedChestplate->getItemName() + " (" + std::to_string(equippedChestplate->getDefence()) + ") Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                armorLevel -= equippedChestplate->getDefence();
		armorLevel += A->getDefence();
                equippedChestplate->unEquip();
                equippedChestplate = A;
                
                A->equip();
                return;
         }
        }
        if (A-> getType() == "Helmet"){
            if (equippedHelmet == nullptr){
                Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                equippedHelmet = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped " + equippedHelmet->getItemName() + " (" + std::to_string(equippedHelmet->getDefence()) + ") Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                armorLevel -= equippedHelmet->getDefence();
		equippedHelmet->unEquip();
		armorLevel += A->getDefence();
                equippedHelmet = A;
                A->equip();
                return;
         }
        }
        if (A-> getType() == "Pants"){
            if (equippedPants == nullptr){
                Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                equippedPants = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped " + equippedPants->getItemName() + " (" + std::to_string(equippedPants->getDefence()) + ") Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                armorLevel -= equippedPants->getDefence();
		equippedPants->unEquip();
		armorLevel += A->getDefence();
                equippedPants = A;
                A->equip();
                return;
         }
        }
        if (A-> getType() == "Boots"){
            if (equippedBoots == nullptr){
                Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                equippedBoots = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped " + equippedBoots->getItemName() + " (" + std::to_string(equippedBoots->getDefence()) + ") Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                armorLevel -= equippedBoots->getDefence();
		equippedBoots->unEquip();
		armorLevel += A->getDefence();
                equippedBoots = A;
                A->equip();
                return;
         }
        }


    }
}






void Character::equip(int pos){
    Item* i = inventory[pos];
    Consumable* C = dynamic_cast<Consumable*>(i);
    if (C) {
        currHP += C->getValue();
        inventory.erase(inventory.begin() + pos);
        delete C;
        return;
    }
    Weapon* W = dynamic_cast<Weapon*>(i);
    if (W) {
         if (equippedWeapon == nullptr){
            Notify("Equipped " + W->getItemName() + " (" + std::to_string(W->getDamage()) + ")");
            equippedWeapon = W;
            W->equip();
            return;
         }
         else{
            Notify("Unequipped " + equippedWeapon->getItemName() + " (" + std::to_string(equippedWeapon->getDamage()) + ") Equipped " + W->getItemName() + " (" + std::to_string(W->getDamage()) + ")");
            equippedWeapon->unEquip();
            equippedWeapon = W;
            W->equip();
            return;
         }
    }
    Armor* A = dynamic_cast<Armor*>(i);
    if (A){
        if (A-> getType() == "Chestplate"){
            if (equippedChestplate == nullptr){
                Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                equippedChestplate = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped " + equippedChestplate->getItemName() + " (" + std::to_string(equippedChestplate->getDefence()) + ") Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                armorLevel -= equippedChestplate->getDefence();
		equippedChestplate->unEquip();
		armorLevel += A->getDefence();
                equippedChestplate = A;
                A->equip();
                return;
         }
        }
        if (A-> getType() == "Helmet"){
            if (equippedHelmet == nullptr){
                Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                equippedHelmet = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped " + equippedHelmet->getItemName() + " (" + std::to_string(equippedHelmet->getDefence()) + ") Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                armorLevel -= equippedHelmet->getDefence();
		equippedHelmet->unEquip();
                equippedHelmet = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
         }
        }
        if (A-> getType() == "Pants"){
            if (equippedPants == nullptr){
                Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                equippedPants = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped " + equippedPants->getItemName() + " (" + std::to_string(equippedPants->getDefence()) + ") Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                armorLevel -= equippedPants->getDefence();
		equippedPants->unEquip();
                equippedPants = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
         }
        }
        if (A-> getType() == "Boots"){
            if (equippedBoots == nullptr){
                Notify("Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                equippedBoots = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped " + equippedBoots->getItemName() + " (" + std::to_string(equippedBoots->getDefence()) + ") Equipped " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
                armorLevel -= equippedBoots->getDefence();
		equippedBoots->unEquip();
                equippedBoots = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
         }
        }

    }

}

Character::Character(int setLevel)
{

    if (setLevel > 0)
    {
        level = setLevel;

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
    }
    else
    {
        throw invalid_argument("Level must be positive");
    }
}
void Character::Attach(Observer *observer)
{
    observers.push_back(observer);
}
void Character::Notify(string attribute, int newValue, int oldValue)
{
    for (auto &observer : observers)
    {
        observer->Update(attribute, newValue, oldValue);
    }
}


void Character::Notify(){
    for (auto& observer: observers){
	observer->Update(this);
    }
}

void Character::Detach(Observer *observer)
{
    for (auto it = observers.begin(); it != observers.end();)
    {
        if (*it == observer)
        {
          it = observers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

int Character::generateAbilityScores()
{
    int n = 4;
    int roll[4];
    for (int i = 0; i < n; i++)
    { // rolling 4d6
        int high = 6;
        int low = 1;
        roll[i] = rand() % (high - low) + low;
    }
    sort(roll, roll + n);               // dropping the lowest roll
    return roll[1] + roll[2] + roll[3]; // summing the 3 highest rolls
}
int Character::calculateModifiers(int points)
{
    float difference = points - 10;
    float modifier = difference / 2;
    return floor(modifier);
}
int Character::calculateHitPoints()
{
    int hitDie = 10; // fighter hit die (d10)
    int hitDieRoll;
    int high;
    int low = 1;
    if (getLevel() == 1)
    {
        hitDieRoll = 1;
    }
    else
    {
        if (getLevel() < hitDie)
        {
            high = getLevel();
        }
        else
        {
            high = hitDie;
        }
        hitDieRoll = rand() % (high - low) + low;
    }
    Notify("Hit Points", hitPoints, getConstitutionMod() + level + hitDieRoll);
    return getConstitutionMod() + level + hitDieRoll;
}
int Character::calculateArmorClass()
{
    return getDexterityMod();
}
int Character::calculateAttackBonus()
{
    return level + getStrengthMod() + getDexterityMod();
}
int Character::calculateDamageBonus()
{
    return getStrengthMod();
}

void Character::setName(string newName){
    name = newName;
    Notify();
}

int Character::calculateAttackPerRound()
{

    if (level % 5 == 0)
    {
        attackPerRound ++;
    }

    return attackPerRound;
}
// Setter for level
void Character::setLevel(int newLevel)
{
    Notify("Level", level, newLevel);
    if (newLevel > 0)
    {
        level = newLevel;
        recalculateAttributes();
	Notify();
    }
    else
    {
        throw invalid_argument("Level must be positive");
    }
}
void Character::setStrength(int newStrength)
{
    Notify("Strength", strength, newStrength);
    strength = newStrength;
    strengthMod = calculateModifiers(strength);
    recalculateAttributes();
}
void Character::setDexterity(int newDexterity)
{
    Notify("Dexterity", dexterity, newDexterity);
    dexterity = newDexterity;
    dexterityMod = calculateModifiers(dexterity);
    recalculateAttributes();
}
void Character::setConstitution(int newConstitution)
{
    Notify("Constitution", constitution, newConstitution);
    constitution = newConstitution;
    constitutionMod = calculateModifiers(constitution);
    recalculateAttributes();
}
void Character::setIntelligence(int newIntelligence)
{
    Notify("Intelligence", intelligence, newIntelligence);
    intelligence = newIntelligence;
    intelligenceMod = calculateModifiers(intelligence);
    recalculateAttributes();
}
void Character::setWisdom(int newWisdom)
{
    Notify("Wisdom", wisdom, newWisdom);
    wisdom = newWisdom;
    wisdomMod = calculateModifiers(wisdom);
    recalculateAttributes();
}
void Character::setCharisma(int newCharisma)
{
    Notify("Charisma", charisma, newCharisma);
    charisma = newCharisma;
    charismaMod = calculateModifiers(charisma);
    recalculateAttributes();
}
// increase (buff and debuff)
void Character::increaseLevel(int levelUp)
{
    if (level + levelUp > 0)
    {
        level += levelUp;
        recalculateAttributes(); // attributes are recalculated after a level change
	cout << "Correct function\n";
	Notify();
    }
    else
    {
        throw invalid_argument("New Level must be positive");
    }
}
void Character::increaseStrength(int buffStrength)
{
    Notify("Strength", strength, (strength + buffStrength));
    strength += buffStrength;
    strengthMod = calculateModifiers(strength);
    recalculateAttributes();
}
void Character::increaseDexterity(int buffDexterity)
{
    Notify("Dexterity", dexterity, (dexterity + buffDexterity));
    dexterity += buffDexterity;
    dexterityMod = calculateModifiers(dexterity);
    recalculateAttributes();
}
void Character::increaseConstitution(int buffConstitution)
{
    Notify("Constitution", constitution, (constitution + buffConstitution));
    constitution += buffConstitution;
    constitutionMod = calculateModifiers(constitution);
    recalculateAttributes();
}
void Character::increaseIntelligence(int buffIntelligence)
{
    Notify("Intelligence", intelligence, (intelligence + buffIntelligence));
    intelligence += buffIntelligence;
    intelligenceMod = calculateModifiers(intelligence);
    recalculateAttributes();
}
void Character::increaseWisdom(int buffWisdom)
{
    Notify("Wisdom", wisdom, (wisdom + buffWisdom));
    wisdom += buffWisdom;
    wisdomMod = calculateModifiers(wisdom);
    recalculateAttributes();
}
void Character::increaseCharisma(int buffCharisma)
{
    Notify("Charisma", charisma, (charisma + buffCharisma));
    charisma += buffCharisma;
    charismaMod = calculateModifiers(charisma);
    recalculateAttributes();
}
// Recalculate attributes that depend on level or modifiers
void Character::recalculateAttributes()
{
    hitPoints = calculateHitPoints();
    armorClass = calculateArmorClass();
    attackBonus = calculateAttackBonus();
    damageBonus = calculateDamageBonus();
}
// Equip gear (as strings for simplicity for now)
void Character::equipArmor(string newArmor) { armor = newArmor; }
void Character::equipShield(string newShield) { shield = newShield; }
void Character::equipWeapon(string newWeapon) { weapon = newWeapon; }
void Character::equipBoots(string newBoots) { boots = newBoots; }
void Character::equipRing(string newRing) { ring = newRing; }
void Character::equipHelmet(string newHelmet) { helmet = newHelmet; }
// getters for Character stats
int Character::getLevel() const { return level; }
int Character::getHitPoints() const { return hitPoints; }
int Character::getArmorClass() const { return armorClass; }
int Character::getAttackBonus() const { return attackBonus; }
int Character::getDamageBonus() const { return damageBonus; }
// getters for abilities
int Character::getStrength() const { return strength; }
int Character::getDexterity() const { return dexterity; }
int Character::getConstitution() const { return constitution; }
int Character::getIntelligence() const { return intelligence; }
int Character::getWisdom() const { return wisdom; }
int Character::getCharisma() const { return charisma; }
// getters for abilitiy modifiers
int Character::getStrengthMod() const { return strengthMod; }
int Character::getDexterityMod() const { return dexterityMod; }
int Character::getConstitutionMod() const { return constitutionMod; }
int Character::getIntelligenceMod() const { return intelligenceMod; }
int Character::getWisdomMod() const { return wisdomMod; }
int Character::getCharismaMod() const { return charismaMod; }
// getters for equipment
string Character::getArmor() const { return armor; }
string Character::getShield() const { return shield; }
string Character::getWeapon() const { return weapon; }
string Character::getBoots() const { return boots; }
string Character::getRing() const { return ring; }
string Character::getHelmet() const { return helmet; }

string Character::toString()
{
    string output = "";
    // Print attributes
    output += "Character: " + name + "\n";
    output += "Level: " + to_string(getLevel()) + "\n";
    output += "Hit Points: " + to_string(getHitPoints()) + "\n";
    output += "Armor Class: " + to_string(getArmorClass()) + "\n";
    output += "Attack Bonus: " + to_string(getAttackBonus()) + "\n";
    output += "Damage Bonus: " + to_string(getDamageBonus()) + "\n";
    // Print ability scores
    output += "Ability Scores:";
    output += "\n";
    output += "  Strength: " + to_string(getStrength()) + " (Mod: " + to_string(getStrengthMod()) + ")" + "\n";
    output += "  Dexterity: " + to_string(getDexterity()) + " (Mod: " + to_string(getDexterityMod()) + ")" + "\n";
    output += "  Constitution: " + to_string(getConstitution()) + " (Mod: " + to_string(getConstitutionMod()) + ")" + "\n";
    output += "  Intelligence: " + to_string(getIntelligence()) + " (Mod: " + to_string(getIntelligenceMod()) + ")" + "\n";
    output += "  Wisdom: " + to_string(getWisdom()) + " (Mod: " + to_string(getWisdomMod()) + ")" + "\n";
    output += "  Charisma: " + to_string(getCharisma()) + " (Mod: " + to_string(getCharismaMod()) + ")" + "\n";
    // Print equipment
    output += "Equipment:";
    output += "\n";
    output += "  Armor: " + (getArmor().empty() ? "None" : getArmor()) + "\n";
    output += "  Shield: " + (getShield().empty() ? "None" : getShield()) + "\n";
    output += "  Weapon: " + (getWeapon().empty() ? "None" : getWeapon()) + "\n";
    output += "  Boots: " + (getBoots().empty() ? "None" : getBoots()) + "\n";
    output += "  Ring: " + (getRing().empty() ? "None" : getRing()) + "\n";
    output += "  Helmet: " + (getHelmet().empty() ? "None" : getHelmet()) + "\n";
    return output;
}
void Character::printCharacter()
{
    // Print attributes
    cout << "Level: " << getLevel() << "\n";
    cout << "Hit Points: " << getHitPoints() << "\n";
    cout << "Armor Class: " << getArmorClass() << "\n";
    cout << "Attack Bonus: " << getAttackBonus() << "\n";
    cout << "Damage Bonus: " << getDamageBonus() << "\n";
    // Print ability scores
    cout << "Ability Scores:"
         << "\n";
    cout << "  Strength: " << getStrength() << " (Mod: " << getStrengthMod() << ")"
         << "\n";
    cout << "  Dexterity: " << getDexterity() << " (Mod: " << getDexterityMod() << ")"
         << "\n";
    cout << "  Constitution: " << getConstitution() << " (Mod: " << getConstitutionMod() << ")"
         << "\n";
    cout << "  Intelligence: " << getIntelligence() << " (Mod: " << getIntelligenceMod() << ")"
         << "\n";
    cout << "  Wisdom: " << getWisdom() << " (Mod: " << getWisdomMod() << ")"
         << "\n";
    cout << "  Charisma: " << getCharisma() << " (Mod: " << getCharismaMod() << ")"
         << "\n";
    // Print equipment
    cout << "Equipment:"
         << "\n";
    cout << "  Armor: " << (getArmor().empty() ? "None" : getArmor()) << "\n";
    cout << "  Shield: " << (getShield().empty() ? "None" : getShield()) << "\n";
    cout << "  Weapon: " << (getWeapon().empty() ? "None" : getWeapon()) << "\n";
    cout << "  Boots: " << (getBoots().empty() ? "None" : getBoots()) << "\n";
    cout << "  Ring: " << (getRing().empty() ? "None" : getRing()) << "\n";
    cout << "  Helmet: " << (getHelmet().empty() ? "None" : getHelmet()) << "\n";
}

// Test constructor and level initialization
void testConstructor()
{
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
void testIncreaseLevel()
{
    Character testCharacter(1);
    testCharacter.increaseLevel(1);
    assert(testCharacter.getLevel() == 2);
    cout << "testIncreaseLevel passed\n";
}

// Test strength attribute and modifier
void testStrengthAttribute()
{
    Character testCharacter(1);
    int initialStrength = testCharacter.getStrength();
    testCharacter.increaseStrength(5);
    assert(testCharacter.getStrength() == initialStrength + 5);
    cout << "testStrengthAttribute passed\n";
}

// Test armor equipment
void testEquipArmor()
{
    Character testCharacter(1);
    testCharacter.equipArmor("Chain Mail");
    assert(testCharacter.getArmor() == "Chain Mail");
    cout << "testEquipArmor passed\n";
}

void testPrint()
{
    Character testCharacter(1);
    testCharacter.printCharacter();
    cout << "testPrint passed\n";
}

// // Optionally, the commented main function can be used for quick testing or demonstration.
// int main() {
//     srand(time(0)); // create random seed

//     //testing Character Strategy
//     HumanPlayerStrategy hs;
//     AggressorStrategy as;
//     FriendlyStrategy fs;
//     //HumanPlayerStrategy
//     Character char1(&hs);
//     char1.performMoveAction();
//     char1.performAttackAction();
//     char1.performFreeAction();
//     //AggressorStrategy
//     char1.setStrategy(&as);
//     char1.performMoveAction();
//     char1.performAttackAction();
//     char1.performFreeAction();
//     //FriendlyStrategy
//     char1.setStrategy(&fs);
//     char1.performMoveAction();
//     char1.performAttackAction();
//     char1.performFreeAction();
//     //Changing from FriendlyStrategy to AggressorStrategy
//     char1.takeDmg(1);
//     char1.performMoveAction();
//     char1.performAttackAction();
//     char1.performFreeAction();

//     return 0;
// }
