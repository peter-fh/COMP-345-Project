#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Items
{
protected:
    string type;
    int enchantment;

public:
    virtual string getType() const = 0;
    virtual string getEnchantment() const = 0;
};

//------------------------ HELMET CLASS ------------------------
class Helmet : public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Helmet() : bonus(0)
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

    string getType() const override
    {
        return "Helmet";
    }

    string getEnchantment() const override
    {
        string info = enchantmentType + ", " + to_string(bonus);
        return info;
    }
};

//------------------------ ARMOR CLASS ------------------------
class Armor : public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Armor() : bonus(0)
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

    string getType() const override
    {
        return "Armor";
    }

    string getEnchantment() const override
    {
        string info = enchantmentType + ", " + to_string(bonus);
        return info;
    }
};

//------------------------ SHIELD CLASS ------------------------
class Shield : public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Shield() : bonus(0)
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

    string getType() const override
    {
        return "Shield";
    }

    string getEnchantment() const override
    {
        string info = enchantmentType + ", " + to_string(bonus);
        return info;
    }
};

//------------------------ RING CLASS ------------------------
class Ring : public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Ring() : bonus(0)
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

    string getType() const override
    {
        return "Ring";
    }

    string getEnchantment() const override
    {
        string info = enchantmentType + ", " + to_string(bonus);
        return info;
    }
};

//------------------------ BELT CLASS ------------------------
class Belt : public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Belt() : bonus(0)
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

    string getType() const override
    {
        return "Belt";
    }

    string getEnchantment() const override
    {
        string info = enchantmentType + ", " + to_string(bonus);
        return info;
    }
};

//------------------------ BOOTS CLASS ------------------------
class Boots : public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Boots() : bonus(0)
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

    string getType() const override
    {
        return "Boots";
    }

    string getEnchantment() const override
    {
        string info = enchantmentType + ", " + to_string(bonus);
        return info;
    }
};

//------------------------ WEAPON CLASS ------------------------
class Weapon : public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Weapon() : bonus(0)
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

    string getType() const override
    {
        return "Weapon";
    }

    string getEnchantment() const override
    {
        string info = enchantmentType + ", " + to_string(bonus);
        return info;
    }
};

// int main()
// {
//     Helmet helmet1;
//     Armor armor1;
//     Shield shield1;
//     Ring ring1;
//     Belt belt1;
//     Boots boots1;
//     Weapon weapon1;
//     std::cout << weapon1.getEnchantment() << std::endl;
//     return 0;
// }
