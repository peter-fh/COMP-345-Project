#pragma once
#include "Item.h"

class Weapon : public Item{
    public:
        Weapon(int base, std::string nom);
        int baseDamage;
        bool equipped();
        void equip() override;
        int getDamage();
        void unEquip();
};
