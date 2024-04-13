#include "Corpse.h"
#include <fstream>
#include <iostream>
#include <sstream>



Item* Corpse::loot(int index){
    if (index-1 > inventory.size() || index < 1){
	std::cout << "\nInvalid Selection";
	return nullptr;
    }
    else{
	Item* selection = inventory[index-1];
	inventory.erase(inventory.begin() + index-1);
	return selection;
    }
}

void Corpse::reget(){
    int index = 0;
    for (Item* item : inventory){
        index++;
        std::cout << "\n  " << index << ": " << item->getItemName();
    }
    index++;
    std::cout << "\n    " << index << ": Exit";
}

void Corpse::search(){
    if (inventory.size() == 0){
        cout<<"inventory null\n";

        std::cout << "\nCorpse empty";
        return;
    }
    else{
        std::cout << "\nInventory Contains\n";
    }
    int index=1;
    for (Item* item : inventory){
        std::cout << "\n(" << index << "): " << item->getItemName() << "\n";
    }
}

void Corpse::determineSymbol(){
    setSymbol('X');
}
Corpse::Corpse(Enemy* e){
    inventory = e->inventory;
    determineSymbol();
}
Corpse::Corpse(std::vector<Item*> setContents){
    inventory = setContents;
    determineSymbol();
}
Corpse::Corpse(){
    determineSymbol();
}


int Corpse::getInvSize(){
    return inventory.size();
}

void Corpse::pickup(Item *i)
{
    inventory.push_back(i);
    i->pickup();
}


void Corpse::saveCorpse(string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for saving." << std::endl;
        return;
    }
    file << "X:" << getX() << "\n";
    file << "Y:" << getY() << "\n";
    file << "Loot:\n";

    if (inventory[0] == nullptr){
        std::cout << "\nCorpse empty";
        return;
    }
    for (Item* item : inventory){
        file<< item->getItemNameAndType()<<"\n";
    }
}

Corpse Corpse::loadCorpse(string filename){ 
    Corpse corps;
    std::ifstream file(filename);
    std::string line;
    std::vector<Item*> v;
    int x,y;



if (!file.is_open())
    {
        cout<<"no file\n";
        throw std::runtime_error("Could not open corpse file");
    }

    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::string key;
        if (getline(iss, key, ':'))
        {
            cout<<key<<endl;
            std::string value;
            getline(iss, value);

            if (key == "X")
            {
                x = stoi(value);
            }
            else if (key == "Y")
            {
                y = stoi(value);
            }
            else if (key == "Loot")
            {
                cout<<"lootloot\n";
                while (getline(file, line) && !line.empty())
                {
                    cout<<"while loop\n";

                    std::istringstream itemStream(line);
                    std::string itemType;
                    getline(itemStream, itemType, ',');

                    if (itemType == "Armour")
                    {
                        std::string defense, armorName, armorType, toEquip;

                        getline(itemStream, armorName, '|');
                        getline(itemStream, armorType, '(');
                        getline(itemStream, defense, ')');
                        Armor *armor1 = new Armor(armorName, armorType, int(stoi(defense)));
                        cout<<"armor\n";
                        v.push_back(armor1);
                    }
                    else if (itemType == "Weapon")
                    {
                        std::string damage, weaponName, toEquip;
                        getline(itemStream, weaponName, '(');
                        getline(itemStream, damage, ')');
                        Weapon *weapon1 = new Weapon(int(stoi(damage)), weaponName);
                        cout<<"weapon\n";
                        v.push_back(weapon1);
                    }
                }
            }
        }
    }
    file.close();
    corps = Corpse(v);
    corps.setX(x);
    corps.setY(y);


    return corps;
}
