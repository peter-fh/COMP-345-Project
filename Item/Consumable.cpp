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
