#include "../Dice/Dice.h"
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include "Consumable.h"
#include <vector>
#include "../Character/Character.h"



class Loot{
    public:
        Dice RNGesus;
        static std::vector<Item*> generateChestLoot();


        static Item* generateWeapon();
        static Item* generateBoots();
        static Item* generatePants();
        static Item* generateHelmet();
        static Item* generateChestplate();

    private:
        Character* playerChar;
        //in game progress we will attach the character so the loot scales with the level later

};
