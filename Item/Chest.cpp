#include "Chest.h"

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
    cout << "entering openChest()\n";
    /* if (contents[0] == nullptr){
        std::cout << "\nChest empty";
        return;
    }
    else{
        std::cout << "\nChest Contains";
    } */
    int index = 1;
    for (Item* item : contents){

        std::cout << "\n  " << index << ": " << item->getItemName();
	index++;
    }
    cout << "exiting openChest()\n";
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

