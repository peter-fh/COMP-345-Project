#include "Key.h"
#include <iostream>
#include <fstream>
#include "Armor.h"
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

Key::Key(int c)
{
    const int code = c;
}

Key::Key()
{
    const int code = 0;
}

int Key::getCode()
{
    return code;
}

void Key::determineSymbol()
{
    setSymbol('K');
}

void saveItem(const Item &item, const std::string &filename)
{
    std::ofstream file(filename, std::ios::app);
    if (file.is_open())
    {
        item.serialize(file);
    }
    else
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
    file.close();
}