#include "Corpse.h"



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
    if (inventory[0] == nullptr){
        std::cout << "\nCorpse empty";
        return;
    }
    else{
        std::cout << "\nInventory Contains";
    }
    for (Item* item : inventory){
        std::cout << "\n  " << item->getItemName();
    }
}

void Corpse::determineSymbol(){
    setSymbol('X');
}
Corpse::Corpse(Enemy* e){
    inventory = e->inventory;
    determineSymbol();
}
int Corpse::getInvSize(){
    return inventory.size();
}


