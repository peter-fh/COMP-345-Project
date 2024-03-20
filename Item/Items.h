#include <iostream>
#include <vector>
#include <string>

using std::string;


class Items
{
protected:
    string type;
    int enchantment;

public:
    virtual string getType() const = 0;
    virtual string getEnchantment() const = 0;
};



class Helmet : public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Helmet();        
    string getType() const override;
    string getEnchantment() const override;

};

class Armor: public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Armor();        
    string getType() const override;
    string getEnchantment() const override;

};

class Shield: public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Shield();        
    string getType() const override;
    string getEnchantment() const override;

};

class Ring: public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Ring();        
    string getType() const override;
    string getEnchantment() const override;

};


class Belt: public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Belt();        
    string getType() const override;
    string getEnchantment() const override;

};


class Boots: public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Boots();        
    string getType() const override;
    string getEnchantment() const override;

};


class Weapon: public Items
{
private:
    int bonus;
    string enchantmentType;

public:
    Weapon();        
    string getType() const override;
    string getEnchantment() const override;

};
