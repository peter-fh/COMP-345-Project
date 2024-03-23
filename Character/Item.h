#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

class Item{
    public:
        std::string itemName;
        bool held = false;
        void pickup();
        void drop();
        virtual std::string getName();
        virtual void equip();
};

#endif // ITEM_H
