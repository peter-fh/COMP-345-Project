#include "Loot.h"
#include <iostream>
#include <string>
#include <vector>

class Chest{
    public:
        std::vector<Item*> contents;
        Chest();
        Chest(std::vector<Item*> setContents);
        void openChest();
        Item* takeItem(int index);
        void reget();
        int amount;
        int getNumOfContents();
};
