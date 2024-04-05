#pragma once
#include <string>
#include <vector>
#include "../Item/Item.h"
#include "Enemy.h"


class Character;


class Corpse{
    public:
        std::vector<Item*> inventory;
        Corpse(Enemy* e);
        void search();
        Item* loot(int i);
};
