#include "Weapon.h"

Weapon::Weapon(int base, std::string nom){
    baseDamage = base;
    held = false;
    itemName = nom;
}
void Weapon::equip(){held = true;}
void Weapon::unEquip(){held = false;}
bool Weapon::equipped(){return held;}

int Weapon::getDamage(){return baseDamage;
}

std::string Weapon::getItemName(){
    return itemName + " (" + std::to_string(baseDamage) + ")";
}
