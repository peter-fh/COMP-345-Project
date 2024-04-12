#pragma once
#include <iostream>
#include <string>
#include "Item.h"

class Armor : public Item
{
public:
    Armor(std::string name, std::string type, int defence);
    Armor();
    std::string type;
    int defence;
    std::string getType();
    int getDefence();
    std::string getItemName() override;
    std::string getSimpleItemName();

    void serialize(std::ostream &out) const override;
    void deserialize(std::istream &in) override;
};
