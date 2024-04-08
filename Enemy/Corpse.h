#pragma once
#include <string>
#include <vector>
#include "../Item/Item.h"
#include "Enemy.h"
#include "../Map/Mappable.h"

class Corpse : public Mappable{
    public:
        std::vector<Item*> inventory;
        Corpse(Enemy* e);
        void search();
        Item* loot(int i);
        char getSymbol() override;
};
