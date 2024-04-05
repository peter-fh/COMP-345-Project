#include "Corpse.h"


void Corpse::search(){
    int index = 1;
    for (Item* item :  Corpse::inventory) {
        if (item != nullptr) {
            cout << "  " << index++ << ": " << item->getItemName();
        }
}
}
Item* Corpse::loot(int i){
    return inventory[i];
}

Corpse::Corpse(Enemy* e){
    inventory = e->inventory;
}


