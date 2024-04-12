
#pragma once
#include "Item.h"

class Weapon : public Item
{
public:
    Weapon(int base, std::string type, std::string nom);
    Weapon();
    int baseDamage;
    std::string weaponType;
    int getDamage();
    void unEquip();
    std::string getItemName() override;
    std::string getSimpleItemName();
    std::string getWeaponType();

    void serialize(std::ostream &out) const override;
    void deserialize(std::istream &in) override;
};
