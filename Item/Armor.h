#pragma once
#include <iostream>
#include <string>
#include "Item.h"


class Armor : public Item{
    public:
        Armor(std::string name, std::string type, int defence);
        std::string type;
        int defence;
        void equip() override;
        void unEquip();
        std::string getType();
        int getDefence();
};
