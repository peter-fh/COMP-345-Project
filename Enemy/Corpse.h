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
        Corpse(std::vector<Item*> setContents);
        Corpse();
        void search();
        Item* loot(int i);
        void determineSymbol() override;
        void reget();
        void pickup(Item *i);
        int getInvSize();
        void saveCorpse(string filename);
        static Corpse loadCorpse(string filename);
};
