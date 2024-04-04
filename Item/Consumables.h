
#pragma once
#include <iostream>
#include <string>
#include "Item.h"


class Consumable : public Item{
    public:
        ~Consumable();
        Consumable(std::string name, int value);
        int value;
        void equip() override; //consume but
        int getValue();

};

