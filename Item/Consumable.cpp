#include "Consumable.h"


Consumable::Consumable(std::string n, int val){
    itemName = n;
    value = val;
}
void Consumable::equip(){
    value = 0;
}
Consumable::~Consumable(){
    delete[] this;
}
int Consumable::getValue(){return value;}

std::string Consumable::getItemNameAndType(){
    return "Consumable," + itemName +"(" + std::to_string(value) + ")";
}