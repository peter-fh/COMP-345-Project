#ifndef LOOT_H
#define LOOT_H


#include "../Dice/Dice.h"
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include "Consumable.h"
#include <vector>

class Character;

class Loot{
    public:
        Dice RNGesus;
        static std::vector<Item*> generateChestLoot();


        static Item* generateWeapon();
        static Item* generateBoots();
        static Item* generatePants();
        static Item* generateHelmet();
        static Item* generateChestplate();
        static Item* generateWeapon(int i);
        static Item* generateBoots(int i);
        static Item* generatePants(int i);
        static Item* generateHelmet(int i);
        static Item* generateChestplate(int i);

    private:
        Character* playerChar;
        //in game progress we will attach the character so the loot scales with the level later

};

#endif
