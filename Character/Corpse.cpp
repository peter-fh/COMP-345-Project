#include "Corpse.h"

Corpse::Corpse(Character* c)
{
    //eulogy = "Corpse of " + c->getName() + ", perished at level: " + std::to_string(c->getLevel());
    //inventory = c->inventory;
}
std::string Corpse::getEulogy(){
    return eulogy;
}

Item* Corpse::ransack(int i){
    Item* rt = inventory[i];
    inventory.erase(inventory.begin() + i);
    return rt;
}

