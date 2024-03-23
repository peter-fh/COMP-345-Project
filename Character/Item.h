
#pragma once
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
        virtual std::string getItemName();
        virtual void equip();
};

#endif // ITEM_H
