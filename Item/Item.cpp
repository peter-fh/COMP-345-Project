#include "Item.h"

std::string Item::getItemName() { return itemName; }

virtual void serialize(std::ostream &out) const
{
    out << itemName << ' ' << held << ' ' << key;
}
