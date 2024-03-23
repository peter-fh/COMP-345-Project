#include "Item.h"



std::string Item::getName(){return itemName;}
void Item::drop(){held = false;}
void Item::pickup(){held = true;}

void Item::equip(){held = true;}
