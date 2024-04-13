#include "Armor.h"

Armor::Armor(std::string nom, std::string t, int d){
    itemName = nom;
    defence = d;
    if (t != "Helmet" && t != "helmet" && t != "pants" && t != "Pants" && t != "boots" && t != "Boots"){
        type = "Chestplate";
        //default if unspecified
    }
    else{
        type = t;
    }
}
std::string Armor::getType(){return type;}
int Armor::getDefence(){return defence;}

void Armor::equip(){held = true;}
void Armor::unEquip(){held = false;}

std::string Armor::getItemName(){
    return itemName + " (" + std::to_string(defence) + ")";
}

std::string Armor::getItemNameAndType(){
    return "Armour," + itemName +"|"+ type +"(" + std::to_string(defence) + ")";
}
