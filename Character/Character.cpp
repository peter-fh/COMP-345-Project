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
#include <iostream>
#include <fstream>
#include <sstream>
#include "Character.h"
#include "../Observer/Observer.h"
#include "../Map/Map.h"
#include "../Enemy/Corpse.h"



using namespace std;


void Character::determineSymbol(){
    setSymbol('P');
    /* if (name == ""){
	setSymbol('P');
    }
    else{
        char p = (char)name[0];
        if (p == 'C' || p == 'E' || p =='B') setSymbol('P');
        else setSymbol((char)name[0]);
    } */
}
void Character::gainXP(int XP){
    std::cout << "Gained " << XP << "XP";
    currXP += XP;
    if (currXP >= levelUpThreshold){
        level++;
        std::cout << "Leveled up to level " << level << " strength and HP increased!";
        currXP -= levelUpThreshold;
        levelUpThreshold++;
        hitPoints += 3;
        strength += 2;
        currHP = hitPoints;
    }
}

Character::Character(){
    int armorLevel = 0;
    levelUpThreshold = 1;
    alive = true;
    std::vector<Item*> inventory;
    inventorySize = 10;
    equippedChestplate = nullptr;
    equippedBoots = nullptr;
    equippedPants = nullptr;
    equippedHelmet = nullptr;
    equippedWeapon = nullptr;
    equippedBow = nullptr;

    level = 1;
    strength = level*2;
    hitPoints = level*3;
    currHP = hitPoints;
    armorClass = armorLevel;
}

std::vector<Observer*> observers;

void Character::inventoryCheck(){
    if (inventory.size() == 0){
        // Notify("  Empty Inventory");
        cout<<"  Empty Inventory"<<endl;
        return;
    }
    int index = 1;
    for (Item* item : Character::inventory) {
        if (item != nullptr) {
            if (item->held)
                cout<<("  " + to_string(index++) + ": " + item->getItemName() + " (Equipped)\n");
            else{
                cout<<("  " + to_string(index++) + ": " + item->getItemName()+ " \n");
            }
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
    int blocked = 0;
    armorLevel = 0;
    if (armorLevel > 10){
	cout << "\narmor level: " << armorLevel << endl;
	    damage -= armorLevel/10;
	    currHP -= damage;
	    blocked = armorLevel/10;
    }
    else{
	    currHP -= damage;
    }
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
    if (inventory.size() >= inventorySize) {
	Notify("Cannot pickup " + i->getItemName() + " inventory full.");
    } else {
	cout << "Picked up " << i->getItemName() << "!" << endl;
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
    if (equippedWeapon == nullptr){
        Notify("Punched enemy for 1 damage");
        return 1;
    }
    int damage = (modifier * (equippedWeapon->getDamage()));
    if (damage == 0){
        Notify("Attack missed");
    }
    else{
        Notify("Attacked for " + std::to_string(damage) + " damage!");
    }
    return damage;
}
int Character::bowAttack(float modifier){
    if (equippedBow == nullptr){
        Notify("No bow equipped");
        return 0;
    }
    int damage = (modifier * (equippedBow->getDamage())), dmg;
    Dice d = Dice(3);
    int num = modifier*5;
    if (num == 0){
        Notify("Attack failed");
        return 0;
    }
    int total = 0;
    Notify(std::to_string(num) + " shots");
    for (int x = 0; x<num; x++){
        dmg = (d.Roll()+3)/5*damage;
        std::cout << "shot " << x+1 << dmg << " damage!\n";
        total += dmg;
    }
    Notify("Attacked with bow for " + std::to_string(total) + " damage!");
    
    return total;
}

std::string Character::status(){
    return name + ": " + std::to_string(currHP) + "/" + std::to_string(hitPoints);

}


void Character::equip(Item* i){
    Consumable* C = dynamic_cast<Consumable*>(i);
    if (C) {
        currHP += C->getValue();
        if (currHP > hitPoints){
            currHP = hitPoints;
        }
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
    Bow* B = dynamic_cast<Bow*>(i);
    if (B) {
        if (equippedBow == nullptr){
            Notify("Equipped: " + B->getItemName());
            equippedBow = B;
            B->equip();
            return;
         }
        else{
            Notify("Unequipped: " + equippedBow->getItemName() + "\nEquipped: " + B->getItemName());
            equippedBow->unEquip();
            equippedBow = B;
            B->equip();
            return;
         }
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
    int armorLevel = 0;
    levelUpThreshold = setLevel;
    alive = true;
    std::vector<Item*> inventory;
    inventorySize = 10;
    equippedChestplate = nullptr;
    equippedBoots = nullptr;
    equippedPants = nullptr;
    equippedHelmet = nullptr;
    equippedWeapon = nullptr;
    equippedBow = nullptr;

    if (setLevel > 0)
    {
        level = setLevel;
        strength = level*2;
        hitPoints = level*3;
        currHP = hitPoints;
        armorClass = armorLevel;
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
int Character::getLevel(){
    return level;
}
int Character::getArmorClass(){
    return armorLevel;
}
int Character::getCurrentHP(){
    return currHP;
}
void Character::setCurrentHP(int newHP ){
    currHP = newHP;
}
int Character::getHitPoints(){
    return hitPoints;
}

int Character::getAttackBonus(){
    if (equippedWeapon == nullptr) return 0;
    return equippedWeapon->getDamage();
}

void Character::heal(){
    currHP = hitPoints;
}

void Character::setName(string newName){
    name = newName;
}
int Character::getStrength(){
    return strength;
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
    // Print ability scores
    output += "Ability Scores:";
    output += "\n";
    output += "  Strength: " + to_string(getStrength()) + "\n";
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
    // Print ability scores
    std::cout << "Ability Scores:"
         << "\n";
    std::cout << "  Strength: " << getStrength() << "\n";
    std::cout << "Equipment:"
         << "\n";
    std::cout << "  Weapon: " + getWeapon() << "\n";
    std::cout << "  Helmet: " + getHelmet() << "\n";
    std::cout << "  Chestplate: " + getChestplate() << "\n";
    std::cout << "  Pants: " + getPants() << "\n";
    std::cout << "  Boots: " + getBoots() << "\n";
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
//FOR MOVING CHARACTER
//********************************************

//SERIALIZATION
void Character::saveCharacter(){
    std::ofstream outFile(getName()+ ".txt");
    outFile << "Name: " << name << "\n";
    outFile << "Level: " << level << "\n";
    outFile << "Current Hit Points: " << currHP << "\n";
    outFile << "Max Hit Points: " << hitPoints << "\n";
    outFile << "Strength: " << strength << "\n\n";

    outFile << "inventory: " << "\n";
    for (Item* item : Character::inventory){
        // if(item->GetClass()->GetFName();)
        outFile << item->getItemNameAndType()<<item->held<<"\n";
    }
    outFile.close();
}

Character Character::loadCharacter(string filename){
    std::ifstream file(filename);
    Character charObj;
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (getline(iss, key, ':')) {
            std::string value;
            getline(iss, value);

            if (key == "Name") {
                string name = value;
            } else if (key == "Level") {
                charObj = Character(stoi(value));
            } else if (key == "Current Hit Points") {
                charObj.setCurrentHP(stoi(value));
            } else if (key == "Max Hit Points") {
                charObj.setHP(stoi(value));
            } else if (key == "Strength") {
                charObj.setStrength(stoi(value));
            } else if (key == "inventory") {
                while (getline(file, line) && !line.empty()) {
                    std::istringstream itemStream(line);
                    std::string itemType;
                    getline(itemStream, itemType, ',');

                    if (itemType == "Armour") {
                        std::string defense, armorName, armorType, toEquip;

                        getline(itemStream, armorName, '|');
                        getline(itemStream, armorType, '(');
                        getline(itemStream, defense, ')');
                        Armor* armor1 = new Armor(armorName,armorType,int(stoi(defense)));
                        charObj.pickup(armor1);
                        // charObj.inventoryCheck();
                        getline(itemStream, toEquip);
                        if(stoi(toEquip)==1){
                            charObj.equip(armor1);
                        }

                    } else if (itemType == "Weapon") {
                        std::string damage, weaponName, toEquip;
                        getline(itemStream, weaponName, '(');
                        getline(itemStream, damage, ')');
                        Weapon* weapon1= new Weapon(int(stoi(damage)),weaponName);
                        charObj.pickup(weapon1);
                        getline(itemStream, toEquip);
                        if(stoi(toEquip)==1){
                            charObj.equip(weapon1);
                        }
                    } else if (itemType == "Consumable") {
                        std::string value, consumableName, toEquip;
                        getline(itemStream, consumableName, '(');
                        getline(itemStream, value, ')');
                        Consumable* consumable1 = new Consumable(consumableName,int(stoi(value)));
                        charObj.pickup(consumable1);
                        getline(itemStream, toEquip);
                        if(stoi(toEquip)==1){
                            charObj.equip(consumable1);
                        }
                    }
                }
            }
        }
    }

    file.close();
    return charObj;
}
