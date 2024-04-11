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
#include <stdexcept>
#include <math.h>
#include "Character.h"
#include "../Observer/Observer.h"
#include "../Map/Map.h"
#include "../Enemy/Corpse.h"



using namespace std;


void Character::determineSymbol(){
    if (name == ""){
	setSymbol('C');
    }
    else{
        setSymbol((char)name[0]);
    }
}


Character::Character(){
}

std::vector<Observer*> observers;

void Character::inventoryCheck(){
    if (inventory.size() == 0){
        Notify("  Empty Inventory");
        return;
    }
    int index = 1;
    for (Item* item : Character::inventory) {
        if (item != nullptr) {
            Notify("  " + to_string(index++) + ": " + item->getItemName());
        }
}}


void Character::openChest(Chest* chest){
    std::string selection;
    int index;
    chest->openChest();
    while (chest->getNumOfContents() != 0){
        selection = "";
        Notify("\nTake item? (y/n)");
        std::getline(cin, selection);
        if (selection != "y" && selection != "Y" && selection != "n" && selection != "N"){ 
            do{
                  std::cout << "\nInvalid, please try again";
                  std::cout << "\nCheck stats? (y/n): ";
                  std::getline(cin, selection);
            } while (selection != "y" && selection != "Y" && selection != "n" && selection != "N");
                  }
        if (selection == "y" || selection == "Y"){
            chest->reget();
            Notify("\n Select Item: ");
            std::getline(cin, selection);
            try{
                index = std::stoi(selection);
                if (index == chest->getNumOfContents()+2) return;
                else{
                    Item* item = chest->takeItem(index);
                    if (item != nullptr) pickup(item);
                }
            }catch(exception e){
                std::cout << "\nInvaid Selection";
            }
    }
        else if (selection == "n" || selection == "N") return;
    

    }
    Notify("\nChest is now empty");
}
void Character::searchCorpse(Corpse* corpse){
    std::string selection;
    int index;
    corpse->search();
    while (corpse->getInvSize() != 0){
        selection = "";
        Notify("\nTake item? (y/n)");
        std::getline(cin, selection);
        if (selection != "y" && selection != "Y" && selection != "n" && selection != "N"){ 
            do{
                  std::cout << "\nInvalid, please try again";
                  std::cout << "\nCheck stats? (y/n): ";
                  std::getline(cin, selection);
            } while (selection != "y" && selection != "Y" && selection != "n" && selection != "N");
                  }
        if (selection == "y" || selection == "Y"){
            corpse->reget();
            Notify("\n Select Item: ");
            std::getline(cin, selection);
            try{
                index = std::stoi(selection);
                if (index == corpse->getInvSize()+2) return;
                else{
                    Item* item = corpse->loot(index);
                    if (item != nullptr) pickup(item);
                }
            }catch(exception e){
                std::cout << "\nInvaid Selection";
            }
    }
        else if (selection == "n" || selection == "N") return;
    

    }
    Notify("\nCorpse is now empty");
}



void Character::takeDamage(int damage){

    int newDamage = damage * armorLevel/100;
    currHP -= newDamage;
    int blocked = damage - newDamage;
    if (blocked > 0){
        std::cout << "Armor blocks " << blocked << " damage";
    }
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
}


void Character::pickup(Item* i){
    if (inventory.size() >= inventorySize) Notify("Cannot pickup " + i->getItemName() + " inventory full.");
    else{
        Notify("Picked up " + i->getItemName() + "!");
        inventory.push_back(i);
        i->pickup();
    }
}


void Character::drop(int pos){
    Item* i = inventory[pos];
    if (i->key){
        Notify("Keys cannot be dropped");
        return;
    }
    i->drop();
    inventory.erase(inventory.begin() + pos);
}


int Character::attack(float modifier){
    int damage = (modifier * (equippedWeapon->getDamage()));
    if (damage == 0){
        Notify("Attack missed");
    }
    else{
        Notify("Attacked for " + std::to_string(damage) + " damage!");
    }
    return damage;
}

std::string Character::status(){
    return name + ": " + std::to_string(currHP) + "/" + std::to_string(hitPoints);
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
            Notify("Equipped " + W->getItemName());
            equippedWeapon = W;
            W->equip();
            return;
         }
         else{
            Notify("Unequipped: " + equippedWeapon->getItemName() + "\nEquipped: " + W->getItemName());
            equippedWeapon->unEquip();
            equippedWeapon = W;
            W->equip();
            return;
         }
    }
    Armor* A = dynamic_cast<Armor*>(i);
    if (A){
        if (A->getType() == "Chestplate"){
            if (equippedChestplate == nullptr){
                Notify("Equipped: " + A->getItemName());
                equippedChestplate = A;
                A->equip();
                armorLevel += A->getDefence();
                return;
            }
            else{
                Notify("Unequipped: " + equippedChestplate->getItemName() + "\nEquipped " + A->getItemName());
                armorLevel -= equippedChestplate->getDefence();
		        armorLevel += A->getDefence();
                equippedChestplate->unEquip();
                equippedChestplate = A;
                
                A->equip();
                return;
         }
        }
        if (A->getType() == "Helmet"){
            if (equippedHelmet == nullptr){
                Notify("Equipped: " + A->getItemName());
                equippedHelmet = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped: " + equippedHelmet->getItemName() +  "\nEquipped: " + A->getItemName());
                armorLevel -= equippedHelmet->getDefence();
		equippedHelmet->unEquip();
		armorLevel += A->getDefence();
                equippedHelmet = A;
                A->equip();
                return;
         }
        }
        if (A->getType() == "Pants"){
            if (equippedPants == nullptr){
                Notify("Equipped: " + A->getItemName());
                equippedPants = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped: " + equippedPants->getItemName() + "\nEquipped: " + A->getItemName());
                armorLevel -= equippedPants->getDefence();
		equippedPants->unEquip();
		armorLevel += A->getDefence();
                equippedPants = A;
                A->equip();
                return;
         }
        }
        if (A->getType() == "Boots"){
            if (equippedBoots == nullptr){
                Notify("Equipped: " + A->getItemName());
                equippedBoots = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped: " + equippedBoots->getItemName() + "\nEquipped: " + A->getItemName() + " (" + std::to_string(A->getDefence()) + ")");
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
            Notify("Equipped: " + W->getItemName());
            equippedWeapon = W;
            W->equip();
            return;
         }
         else{
            Notify("Unequipped: " + equippedWeapon->getItemName() + "\nEquipped: " + W->getItemName());
            equippedWeapon->unEquip();
            equippedWeapon = W;
            W->equip();
            return;
         }
    }
    Armor* A = dynamic_cast<Armor*>(i);
    if (A){
        if (A->getType() == "Chestplate"){
            if (equippedChestplate == nullptr){
                Notify("Equipped " + A->getItemName());
                equippedChestplate = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped: " + equippedChestplate->getItemName() + "\nEquipped: " + A->getItemName());
                armorLevel -= equippedChestplate->getDefence();
		equippedChestplate->unEquip();
		armorLevel += A->getDefence();
                equippedChestplate = A;
                A->equip();
                return;
         }
        }
        if (A->getType() == "Helmet"){
            if (equippedHelmet == nullptr){
                Notify("Equipped: " + A->getItemName());
                equippedHelmet = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped: " + equippedHelmet->getItemName() + "\nEquipped: " + A->getItemName());
                armorLevel -= equippedHelmet->getDefence();
		equippedHelmet->unEquip();
                equippedHelmet = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
         }
        }
        if (A->getType() == "Pants"){
            if (equippedPants == nullptr){
                Notify("Equipped: " + A->getItemName());
                equippedPants = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped: " + equippedPants->getItemName() + "\nEquipped: " + A->getItemName());
                armorLevel -= equippedPants->getDefence();
		equippedPants->unEquip();
                equippedPants = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
         }
        }
        if (A->getType() == "Boots"){
            if (equippedBoots == nullptr){
                Notify("Equipped: " + A->getItemName());
                equippedBoots = A;
		armorLevel += A->getDefence();
                A->equip();
                return;
            }
            else{
                Notify("Unequipped: " + equippedBoots->getItemName() + "\nEquipped: " + A->getItemName());
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
    alive = true;
    std::vector<Item*> inventory;
    inventorySize = 10;
    equippedChestplate = nullptr;
    equippedBoots = nullptr;
    equippedPants = nullptr;
    equippedHelmet = nullptr;
    equippedWeapon = nullptr;

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
        currHP = hitPoints;
        armorClass = calculateArmorClass();
        attackBonus = calculateAttackBonus();
        damageBonus = calculateDamageBonus();
    }
    else
    {
        throw invalid_argument("Level must be positive");
    }
    
}
void Character::Attach(Observer* observer)
{
    observers.push_back(observer);
}
void Character::Notify(std::string attribute, int newValue, int oldValue)
{
    for (auto &observer : observers)
    {
        observer->Update(attribute, newValue, oldValue);
    }
}
void Character::Notify(std::string attribute)
{
    for (auto &observer : observers)
    {
        observer->Update(attribute);
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
    //sort(roll, roll + n);               // dropping the lowest roll
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
int Character::getCurrentHP() {return currHP;}
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
string Character::getChestplate() const { return equippedChestplate->getItemName(); }
string Character::getPants() const { return equippedPants->getItemName(); }
string Character::getWeapon() const { return equippedWeapon->getItemName(); }
string Character::getBoots() const { return equippedBoots->getItemName(); }
string Character::getHelmet() const { return equippedHelmet->getItemName(); }

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
    output += "  Weapon: " + getWeapon() + "\n";
    output += "  Helmet: " + getHelmet() + "\n";
    output += "  Chestplate: " + getChestplate() + "\n";
    output += "  Pants: " + getPants() + "\n";
    output += "  Boots: " + getBoots() + "\n";
    return output;
}
void Character::printCharacter()
{
    // Print attributes
    std::cout << "Level: " << getLevel() << "\n";
    std::cout << "Hit Points: " << getHitPoints() << "\n";
    std::cout << "Armor Class: " << getArmorClass() << "\n";
    std::cout << "Attack Bonus: " << getAttackBonus() << "\n";
    std::cout << "Damage Bonus: " << getDamageBonus() << "\n";
    // Print ability scores
    std::cout << "Ability Scores:"
         << "\n";
    std::cout << "  Strength: " << getStrength() << " (Mod: " << getStrengthMod() << ")"
         << "\n";
    std::cout << "  Dexterity: " << getDexterity() << " (Mod: " << getDexterityMod() << ")"
         << "\n";
    std::cout << "  Constitution: " << getConstitution() << " (Mod: " << getConstitutionMod() << ")"
         << "\n";
    std::cout << "  Intelligence: " << getIntelligence() << " (Mod: " << getIntelligenceMod() << ")"
         << "\n";
    std::cout << "  Wisdom: " << getWisdom() << " (Mod: " << getWisdomMod() << ")"
         << "\n";
    std::cout << "  Charisma: " << getCharisma() << " (Mod: " << getCharismaMod() << ")"
         << "\n";
    // Print equipment
    std::cout << "Equipment:"
         << "\n";
    std::cout << "  Weapon: " + getWeapon() << "\n";
    std::cout << "  Helmet: " + getHelmet() << "\n";
    std::cout << "  Chestplate: " + getChestplate() << "\n";
    std::cout << "  Pants: " + getPants() << "\n";
    std::cout << "  Boots: " + getBoots() << "\n";
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
    std::cout << "testConstructor passed\n";
}

// Test increasing level
void testIncreaseLevel()
{
    Character testCharacter(1);
    testCharacter.increaseLevel(1);
    assert(testCharacter.getLevel() == 2);
    std::cout << "testIncreaseLevel passed\n";
}

// Test strength attribute and modifier
void testStrengthAttribute()
{
    Character testCharacter(1);
    int initialStrength = testCharacter.getStrength();
    testCharacter.increaseStrength(5);
    assert(testCharacter.getStrength() == initialStrength + 5);
    std::cout << "testStrengthAttribute passed\n";
}

// Test armor equipment

void testPrint()
{
    Character testCharacter(1);
    testCharacter.printCharacter();
    std::cout << "testPrint passed\n";
}

//********************************************
//FOR MOVING CHARACTER

bool Character::moveTo(int newX, int newY, Map* currentMap){
    int currentX = this->getX();
    int currentY = this->getY();
    if (currentMap->getEnd().x == newX && currentMap->getEnd().y == newY){
        currentMap->setCell(currentX,currentY,EMPTY);
	this->deactivate();
	cout << name << " has reached the end of the map!" << endl;
	cout << "Press enter to continue: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return true;
    }
    if(currentMap->passable(newX,newY)){
        currentMap->setCell(newX,newY,OCCUPIED, this);
	this->setX(newX);
	this->setY(newY);
        currentMap->setCell(currentX,currentY,EMPTY);
        return true;
    }
    return false;
}

bool Character::attackThere(int targetX, int targetY, Map* currentMap, int dmg){
    // int currentX = this->getXlocation();
    // int currentY = this->getYlocation();
    // const int LARGE_NUM = 2147483647;
    // float distance=LARGE_NUM, currentDist;
    // int x,y,destinationX,destinationY,stepX,stepY;
    // for(x=0;x<currentMap->getWidth();x++){
    //     for(y=0;y<currentMap->getHeight();y++){
    //         if(currentMap->getCell(x,y).character != nullptr){
    //             currentDist = pow((x-currentX),2)+pow((y-currentY),2);
    //             if(currentDist<distance){
    //                 distance = currentDist;
    //                 destinationX = x;
    //                 destinationY = y;
    //             }
    //         }
    //     }
    // }
    /* Character enemy = *currentMap->getCell(targetX,targetY).character;
    if(currentMap->getCell(targetX,targetY).character){
        enemy.setHP(enemy.getHitPoints()-dmg-this->getStrengthMod()); //doesnt work
        cout<<"Attack Successful"<<endl;
        return true;
    }
    else{
        cout<<"Not a Valid Target"<<endl;
        return false;
    }*/
    return false;
} 

//FOR MOVING CHARACTER
//********************************************
