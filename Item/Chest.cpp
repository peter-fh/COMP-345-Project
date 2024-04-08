#include "Chest.h"

Chest::Chest(){
    contents = Loot::generateChestLoot();
    int amount = contents.size();
}
Chest::Chest(){

}

Item* Chest::takeItem(int index){
    if (index-1 > amount || index < 1){
        std::cout << "\nInvalid index";
    }
    else{
        amount--;
        Item* selection = contents[index-1];
        contents[index-1] = nullptr;
        return selection;
    }
}
void Chest::openChest(){
    int index = 0;
    if (contents[0] == nullptr){
        std::cout << "\nChest empty";
        return;
    }
    else{
        std::cout << "\nChest Contains";
    }
    for (Item* item : contents){
        index++;
        std::cout << "\n  " << index << ": " << item->getItemName();
    }
}

void Chest::reget(){
    int index = 0;
    for (Item* item : contents){
        index++;
        std::cout << "\n  " << index << ": " << item->getItemName();
    }
}

int Chest::getNumOfContents(){
    return amount;
}
