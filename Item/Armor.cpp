#include <iostream>
#include <fstream>
#include "Armor.h"
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

Armor::Armor(std::string nom, std::string t, int d)
{
    itemName = nom;
    defence = d;
    if (t != "Helmet" && t != "helmet" && t != "pants" && t != "Pants" && t != "boots" && t != "Boots")
    {
        type = "Chestplate";
        // default if unspecified
    }
    else
    {
        type = t;
    }
}

Armor::Armor()
{
    itemName = "";
    type = "";
    defence = 0;
};

std::string Armor::getType() { return type; }
int Armor::getDefence() { return defence; }

std::string Armor::getSimpleItemName()
{
    return itemName;
}

std::string Armor::getItemName()
{
    return itemName + " (" + std::to_string(defence) + ")";
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

std::unique_ptr<Armor> loadArmor(const std::string &filename, const std::string &searchItemName)
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
            std::unique_ptr<Armor> armor(new Armor());
            iss.seekg(0);            // Reset stream position to the beginning of the line
            armor->deserialize(iss); // Deserialize from the stringstream
            file.close();
            return armor;
        }
    }

    file.close();
    std::cerr << "Armor with name '" << searchItemName << "' not found." << std::endl;
    return nullptr;
}

void Armor::serialize(std::ostream &out) const
{
    Item::serialize(out);
    out << type << ",";
    out << defence << std::endl;
}

void Armor::deserialize(std::istream &in)
{
    Item::deserialize(in);
    std::getline(in, type, ',');
    in >> defence;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    Armor myArmor("Dragon Armor", "Chestplate", 40);
    Armor myArmor1("Diamond Armor", "Helmet", 120);
    std::cout << myArmor.getSimpleItemName() << std::endl;
    // saveItem(myArmor, "./armor_data.txt");
    // saveItem(myArmor1, "./armor_data.txt");
    auto loadedArmor = loadArmor("armor_data.txt", "Dragon Armor");
    if (loadedArmor)
    {
        std::cout << "Loaded Armor: " << loadedArmor->getSimpleItemName() << std::endl;
        std::cout << "Type: " << loadedArmor->getType() << std::endl;
        std::cout << "Defense: " << loadedArmor->getDefence() << std::endl;
    }
    return 0;
}
