#include "Items.h"

using std::to_string;


//------------------------ HELMET CLASS ------------------------
Helmet::Helmet() : bonus(0)
{
    // Seed the random number generator (only once)
    static bool seeded = false;
    if (!seeded)
    {
	srand(time(NULL));
	seeded = true;
    }

    // Randomly select an enchantment
    string possibleEnchantments[] = {"Intelligence", "Wisdom", "Armor class"};

    // Randomly select an index from 0 to the size of possibleEnchantments array
    int index = rand() % 3;

    // Apply the selected enchantment
    string enchantment = possibleEnchantments[index];
    bonus = rand() % 5 + 1;
    enchantmentType = enchantment;
}

string Helmet::getType() const 
{
    return "Helmet";
}

string Helmet::getEnchantment() const 
{
    string info = enchantmentType + ", " + to_string(bonus);
    return info;
}


//------------------------ ARMOR CLASS ------------------------
Armor::Armor() : bonus(0)
{
    // Seed the random number generator (only once)
    static bool seeded = false;
    if (!seeded)
    {
	srand(time(NULL));
	seeded = true;
    }

    // Randomly select an enchantment
    string possibleEnchantments = "Armor class";

    // Apply the selected enchantment
    bonus = rand() % 5 + 1;
    enchantmentType = possibleEnchantments;
}

string Armor::getType() const 
{
    return "Armor";
}

string Armor::getEnchantment() const 
{
    string info = enchantmentType + ", " + to_string(bonus);
    return info;
}


//------------------------ SHIELD CLASS ------------------------
Shield::Shield() : bonus(0)
{
    // Seed the random number generator (only once)
    static bool seeded = false;
    if (!seeded)
    {
	srand(time(NULL));
	seeded = true;
    }

    // Randomly select an enchantment
    string possibleEnchantments = "Armor class";

    // Apply the selected enchantment
    bonus = rand() % 5 + 1;
    enchantmentType = possibleEnchantments;
}

string Shield::getType() const 
{
    return "Shield";
}

string Shield::getEnchantment() const 
{
    string info = enchantmentType + ", " + to_string(bonus);
    return info;
}

//------------------------ RING CLASS ------------------------
Ring::Ring() : bonus(0)
{
    // Seed the random number generator (only once)
    static bool seeded = false;
    if (!seeded)
    {
	srand(time(NULL));
	seeded = true;
    }

    // Randomly select an enchantment
    string possibleEnchantments[] = {"Armor class", "Strength", "Constitution", "Wisdom", "Charisma"};

    // Randomly select an index from 0 to the size of possibleEnchantments array
    int index = rand() % 5;

    // Apply the selected enchantment
    string enchantment = possibleEnchantments[index];
    bonus = rand() % 5 + 1;
    enchantmentType = enchantment;
}

string Ring::getType() const 
{
    return "Ring";
}

string Ring::getEnchantment() const 
{
    string info = enchantmentType + ", " + to_string(bonus);
    return info;
}

//------------------------ BELT CLASS ------------------------
Belt::Belt() : bonus(0)
{
    // Seed the random number generator (only once)
    static bool seeded = false;
    if (!seeded)
    {
	srand(time(NULL));
	seeded = true;
    }

    // Randomly select an enchantment
    string possibleEnchantments[] = {"Strength", "Constitution"};

    // Randomly select an index from 0 to the size of possibleEnchantments array
    int index = rand() % 2;

    // Apply the selected enchantment
    string enchantment = possibleEnchantments[index];
    bonus = rand() % 5 + 1;
    enchantmentType = enchantment;
}

string Belt::getType() const 
{
    return "Belt";
}

string Belt::getEnchantment() const 
{
    string info = enchantmentType + ", " + to_string(bonus);
    return info;
}

//------------------------ BOOTS CLASS ------------------------
Boots::Boots() : bonus(0)
{
    // Seed the random number generator (only once)
    static bool seeded = false;
    if (!seeded)
    {
	srand(time(NULL));
	seeded = true;
    }

    // Randomly select an enchantment
    string possibleEnchantments[] = {"Armor class", "Dexterity"};

    // Randomly select an index from 0 to the size of possibleEnchantments array
    int index = rand() % 2;

    // Apply the selected enchantment
    string enchantment = possibleEnchantments[index];
    bonus = rand() % 5 + 1;
    enchantmentType = enchantment;
}

string Boots::getType() const 
{
    return "Boots";
}

string Boots::getEnchantment() const 
{
    string info = enchantmentType + ", " + to_string(bonus);
    return info;
}


//------------------------ WEAPON CLASS ------------------------
Weapon::Weapon() : bonus(0)
{
    // Seed the random number generator (only once)
    static bool seeded = false;
    if (!seeded)
    {
	srand(time(NULL));
	seeded = true;
    }

    // Randomly select an enchantment
    string possibleEnchantments[] = {"Attack bonus", "Damage bonus"};

    // Randomly select an index from 0 to the size of possibleEnchantments array
    int index = rand() % 2;

    // Apply the selected enchantment
    string enchantment = possibleEnchantments[index];
    bonus = rand() % 5 + 1;
    enchantmentType = enchantment;
}

string Weapon::getType() const 
{
    return "Weapon";
}

string Weapon::getEnchantment() const 
{
    string info = enchantmentType + ", " + to_string(bonus);
    return info;
}

