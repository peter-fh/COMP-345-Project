#ifndef ENEMY_H
#define ENEMY_H



#include "../Item/Item.h"
#include "../Item/Consumable.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Character/Character.h"
#include "../Dice/Dice.h"
#include "../Observer/Observer.h"
#include "../Item/Loot.h"
#include "../Map/Mappable.h"
#include <string>

class Corpse;

class Enemy : public Mappable{
    public:
        Enemy();
        std::string name;
        void takeDamage(int damage);
        int Attack(float mod);
        Corpse kill();
        std::string status();
        std::vector<Item*> inventory;
        bool alive;
        void playerFlee();
        int armorMod, level;
        char getSymbol() override;

        void equipment();

        //TODO for final, armormod as a percentage of damage reduction, eg: 15 armorMod means attack is 85% effective

        Armor *equippedChestplate, *equippedHelmet, *equippedBoots, *equippedPants;

        Weapon* equippedWeapon;
        int maxHP, currentHP;


    private:
        Character* playerCharacter;

};

#endif
