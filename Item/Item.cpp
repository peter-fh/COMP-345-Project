#include "Item.h"



std::string Item::getItemName(){return itemName;}
std::string Item::getItemNameAndType(){return itemName;}
void Item::drop(){held = false;}
void Item::pickup(){held = true;}

void Item::equip(){held = true;}
