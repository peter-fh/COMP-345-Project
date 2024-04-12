#include <iostream>
#include <fstream>
#include "Weapon.h"
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

Weapon::Weapon(int base, std::string type, std::string nom)
{
    baseDamage = base;
    weaponType = type;
    held = false;
    itemName = nom;
}

Weapon::Weapon()
{
    baseDamage = 0;
    itemName = "";
    weaponType = "";
};

void Weapon::unEquip() { held = false; }

int Weapon::getDamage()
{
    // std::cout << "Weapon damage: " << baseDamage << "\n";
    return baseDamage;
}

std::string Weapon::getWeaponType()
{
    return weaponType;
}

std::string Weapon::getItemName()
{
    return itemName + " (" + std::to_string(baseDamage) + ")";
}

std::string Weapon::getSimpleItemName()
{
    return itemName;
}

void saveItem(const Item &item, const std::string &filename)
{
    std::ofstream file(filename, std::ios::app);
    if (file.is_open())
    {
        item.serialize(file);
    }
    else
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
    file.close();
}

void Weapon::serialize(std::ostream &out) const
{
    Item::serialize(out);
    out << weaponType << ",";
    out << baseDamage << std::endl;
}

std::unique_ptr<Weapon> loadWeapon(const std::string &filename, const std::string &searchItemName)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return nullptr;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string itemName;
        std::getline(iss, itemName, ',');
        if (itemName == searchItemName)
        {
            std::unique_ptr<Weapon> weapon(new Weapon());
            iss.seekg(0);
            weapon->deserialize(iss);
            file.close();
            return weapon;
        }
    }

    file.close();
    std::cerr << "Weapon with name '" << searchItemName << "' not found." << std::endl;
    return nullptr;
}

void Weapon::deserialize(std::istream &in)
{
    Item::deserialize(in);
    std::getline(in, weaponType, ',');
    in >> baseDamage;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    Weapon myWeapon(150, "ranged", "big ass sword!");
    Weapon myWeapon1(230, "melee", "small ass sword");
    std::cout << myWeapon.getItemName() << std::endl;

    // saveItem(myWeapon, "./weapon_data.txt");
    // saveItem(myWeapon1, "./weapon_data.txt");

    auto loadedWeapon = loadWeapon("weapon_data.txt", "small ass sword");
    if (loadedWeapon)
    {
        std::cout << "Loaded Weapon: " << loadedWeapon->getSimpleItemName() << std::endl;
        std::cout << "Weapon Type: " << loadedWeapon->getWeaponType() << std::endl;
        std::cout << "Base Damage: " << loadedWeapon->getDamage() << std::endl;
    }
    else
    {
        std::cout << "It fucked up" << std::endl;
    }
    return 0;
}