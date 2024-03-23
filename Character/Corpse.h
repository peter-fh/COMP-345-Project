
#pragma once
#include <string>
#include <vector>
#include "Item.h"


class Character;


class Corpse{
    public:
        std::vector<Item*> inventory;
        Corpse(Character* c);
        std::string eulogy;
        std::string getEulogy();
        Item* ransack(int i);
};
