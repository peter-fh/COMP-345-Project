#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

class Item
{
public:
    std::string itemName;
    bool held = false;
    virtual std::string getItemName() = 0;
    virtual ~Item() {}
    bool key = false;

    virtual void serialize(std::ostream &out) const
    {
        out << itemName << ",";
    }

    virtual void deserialize(std::istream &in)
    {
        std::getline(in, itemName, ',');
    }
};

#endif // ITEM_H
