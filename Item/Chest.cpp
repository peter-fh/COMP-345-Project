#include "Chest.h"
#include <fstream>
#include <iostream>
#include <sstream>

Chest::Chest(){
    contents = Loot::generateChestLoot();
    amount = contents.size();
}
Chest::Chest(std::vector<Item*> setContents){
    contents = setContents;
    amount = contents.size();
}

Item* Chest::takeItem(int index){
    if (index-1 > amount || index < 1){
        std::cout << "\nInvalid Selection";
        return nullptr;
    }
    else{
        amount--;
        Item* selection = contents[index-1];
        contents.erase(contents.begin() + index-1);
        return selection;
    }
}
void Chest::openChest(){
    if (contents[0] == nullptr){
        std::cout << "\nChest empty";
        return;
    }
    else{
        std::cout << "\nChest Contains";
    }
    for (Item* item : contents){
        std::cout << "\n  " << item->getItemName();
    }
}

void Chest::reget(){
    int index = 0;
    for (Item* item : contents){
        index++;
        std::cout << "\n  " << index << ": " << item->getItemName();
    }
    index++;
    std::cout << "\n    " << index << ": Exit";
}

int Chest::getNumOfContents(){
    return amount;
}


void Chest::determineSymbol(){
    setSymbol('C');
}

void Chest::saveChest(string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for saving." << std::endl;
        return;
    }
    file << "X: " << getX() << "\n";
    file << "Y: " << getY() << "\n";
    file << "Number of items: " << getNumOfContents() << "\n";

    if (contents[0] == nullptr){
        std::cout << "\nChest empty";
        return;
    }
    for (Item* item : contents){
        file << "\n  " << item->getItemNameAndType();
    }
}

Chest Chest::loadChest(string filename){
    Armor* armor1 = new Armor("Iron Helmet", "Helmet", 12);
    Armor* armor2 = new Armor("Iron Pants","Pants", 12);
    Armor* armor3 = new Armor("Iron Chestpiece","Chestplate", 12);
    Armor* armor4 = new Armor("Iron Boots","Boots", 12);
    std::vector<Item*> v = {armor1, armor2, armor3, armor4};
    Chest chest = Chest(v);
    std::ifstream file(filename);
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

            if (key == "X")
            {
                chest.setX(stoi(value));
            }
            else if (key == "Y")
            {
                chest.setY(stoi(value));
            }
        }
    }

    return chest;
}
