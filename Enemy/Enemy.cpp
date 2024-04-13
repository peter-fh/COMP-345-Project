#include "Enemy.h"
#include "Corpse.h"
#include <iostream>
#include <fstream>
#include <sstream>

Enemy::Enemy(std::string givenName, int givenLevel, int givenHP, Weapon *weapon, Armor *Helmet, Armor *Chestplate, Armor *Pants, Armor *Boots)
{
    name = givenName;
    level = givenLevel;
    maxHP = givenHP;
    currentHP = givenHP;
    std::vector<Item *> inventory;
    armorMod = 0;
    equippedWeapon = weapon;
    inventory.push_back(weapon);
    equippedHelmet = Helmet;
    inventory.push_back(Helmet);
    armorMod += Helmet->getDefence();
    equippedChestplate = Chestplate;
    inventory.push_back(Chestplate);
    armorMod += Chestplate->getDefence();
    equippedPants = Pants;
    inventory.push_back(Pants);
    armorMod += Pants->getDefence();
    equippedBoots = Boots;
    inventory.push_back(Boots);
    armorMod += Boots->getDefence();
}

void Enemy::giveItem(Item *i)
{
    inventory.push_back(i);
}

Enemy::Enemy()
{
    Dice coinflip = Dice(2);
    std::vector<Item *> inventory;
    int armorMod = 0;

    inventory.push_back(Loot::generateWeapon());
    equippedWeapon = dynamic_cast<Weapon *>(inventory[0]);

    inventory.push_back(Loot::generateChestplate());
    equippedChestplate = dynamic_cast<Armor *>(inventory[1]);
    armorMod += equippedChestplate->getDefence();

    inventory.push_back(Loot::generateBoots());
    equippedBoots = dynamic_cast<Armor *>(inventory[2]);
    armorMod += equippedBoots->getDefence();

    if (coinflip.Roll() == 2)
    {
        inventory.push_back(Loot::generatePants());
        equippedPants = dynamic_cast<Armor *>(inventory.back());
        armorMod += equippedPants->getDefence();
    }
    else
    {
        Armor *b1 = new Armor("Tattered Pants", "Pants", 1);
        inventory.push_back(b1);
        equippedPants = b1;
        armorMod += 1;
    }

    if (coinflip.Roll() == 2)
    {
        inventory.push_back(Loot::generateHelmet());
        equippedHelmet = dynamic_cast<Armor *>(inventory.back());
        armorMod += equippedHelmet->getDefence();
    }
    else
    {
        equippedHelmet = nullptr;
    }

    Dice lvl = Dice(5);
    level = lvl.Roll();
    maxHP = 5 + level;
    currentHP = maxHP;

    Dice speciesDice = Dice(5);
    std::string races[] = {"Goblin", "Human", "Orc", "Elf", "Dwarf"};
    name = races[speciesDice.Roll() - 1];
}

std::string Enemy::status()
{
    return "\n" + name + ": " + std::to_string(currentHP) + "/" + std::to_string(maxHP);
}

Corpse Enemy::kill()
{
    return Corpse(this);
}
void Enemy::playerFlee()
{
    currentHP = maxHP;
}

int Enemy::Attack(float modifier)
{
    int damage = (modifier * ((equippedWeapon->getDamage())));
    if (damage == 0)
    {
        std::cout << "\nAttack missed";
    }
    else
    {
        std::cout << "\n"
                  << name << " attacked for " + std::to_string(damage) + " damage!\n";
    }
    return damage;
}
void Enemy::equipment()
{
    std::cout << "Equipment\n"
              << equippedWeapon->getItemName() << "\n";
    if (equippedHelmet != nullptr)
    {
        std::cout << equippedHelmet->getItemName() << "\n";
    }
    std::cout << equippedChestplate->getItemName() << "\n"
              << equippedPants->getItemName() << "\n"
              << equippedBoots->getItemName();
}

void Enemy::takeDamage(int damage){
    int blocked = 0;
    armorMod = 0;
    if (armorMod > 10){
	    damage -= armorMod/10;
	    currentHP -= damage;
	    blocked = armorMod/10;
    }
    else{
	    currentHP -= damage;
    }
    if (blocked > 0){
        std::cout << "Armor blocks " << blocked << " damage";
    }
    if (currentHP <= 0)
    {
        std::cout << "\n"
                  << name << " slain";
        alive = false;
    }
}

void Enemy::determineSymbol()
{
    this->setSymbol('E');
}

std::string Enemy::getEnemyName() { return name; }

void Enemy::saveEnemy()
{
    std::ofstream outFile("Goblin.txt");
    outFile << "X: " << getX() << "\n";
    outFile << "Y: " << getY() << "\n";
    outFile << "Name: " << name << "\n";
    outFile << "Level: " << level << "\n";
    outFile << "Current HP: " << currentHP << "\n";
    outFile << "Max HP: " << maxHP << "\n\n";

    outFile << "Inventory: "
            << "\n";
    for (Item *item : inventory)
    {
        outFile << item->getItemNameAndType() << item->held << "\n"; // Assumed method
    }
    outFile.close();
}

static Enemy loadEnemy(const std::string &filename)
{
    std::ifstream file(filename);
    Enemy enemyObj;
    std::string line;

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::string key;
        if (getline(iss, key, ':'))
        {
            std::string value;
            getline(iss, value);
            value = value.substr(1); // Remove leading space

            if (key == "X")
            {
                enemyObj.setX(stoi(value));
            }
            else if (key == "Y")
            {
                enemyObj.setY(stoi(value));
            }
            else if (key == "Name")
            {
                enemyObj.name = value;
            }
            else if (key == "Level")
            {
                enemyObj.level = stoi(value);
            }
            else if (key == "Current HP")
            {
                enemyObj.currentHP = stoi(value);
            }
            else if (key == "Max HP")
            {
                enemyObj.maxHP = stoi(value);
            }
            // else if (key == "inventory")
            // {
            //     while (getline(file, line) && !line.empty())
            //     {
            //         std::istringstream itemStream(line);
            //         std::string itemType;
            //         getline(itemStream, itemType, ',');

            //         if (itemType == "Armour")
            //         {
            //             std::string defense, armorName, armorType, toEquip;

            //             getline(itemStream, armorName, '|');
            //             getline(itemStream, armorType, '(');
            //             getline(itemStream, defense, ')');
            //             Armor *armor1 = new Armor(armorName, armorType, int(stoi(defense)));
            //             enemyObj.inventory.push_back(armor1);
            //             // charObj.inventoryCheck();
            //             getline(itemStream, toEquip);
            //             if (stoi(toEquip) == 1)
            //             {
            //                 if (armorType == "boots")
            //                 {
            //                     enemyObj.equippedBoots;
            //                 }

            //                 if (armorType == "chestplace")
            //                 {
            //                     enemyObj.equippedChestplate;
            //                 }

            //                 if (armorType == "helmet")
            //                 {
            //                     enemyObj.equippedHelmet;
            //                 }

            //                 if (armorType == "pants")
            //                 {
            //                     enemyObj.equippedPants;
            //                 }
            //             }
            //         }
            //         else if (itemType == "Weapon")
            //         {
            //             std::string damage, weaponName, toEquip;
            //             getline(itemStream, weaponName, '(');
            //             getline(itemStream, damage, ')');
            //             Weapon *weapon1 = new Weapon(int(stoi(damage)), weaponName);
            //             // enemyObj.equippedWeapon(weapon1);
            //             getline(itemStream, toEquip);
            //             if (stoi(toEquip) == 1)
            //             {
            //                 // enemyObj.equippedWeapon(weapon1);
            //             }
            //         }
            //     }
            // }
        }
    }

    file.close();
    return enemyObj;
}

;
