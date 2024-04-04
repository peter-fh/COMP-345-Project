#include "Loot.h"


std::vector<Item*> Loot::generateChestLoot(){
    Dice RNGesus = Dice(100);
    int table = RNGesus.Roll()/20;
    std::vector<Item*> lootTable;
    int pull, mod, wildcard;
    std::string classMod;

    switch(table){
        case(1):{
            //1 weapon, 1 random armor piece, 1 consumable
            mod = RNGesus.Roll()/10;
            Consumable c1 = Consumable("Potion of Healing", mod);
            lootTable.push_back(&c1);
            pull = RNGesus.Roll()/25;
            mod = RNGesus.Roll()/10;
            wildcard = RNGesus.Roll();
            if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard = 1){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard = 2){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard = 3){
                    classMod = "Iron";
                    mod += 5;
                }
            }
            switch(pull){
                case(1):{
                    Armor a1 = Armor(classMod + " Helmet", "Helmet", mod);
                    lootTable.push_back(&a1);
                    break;
                }
                case(2):{
                    Armor a1 = Armor(classMod + " Pants", "Pants", mod);
                    lootTable.push_back(&a1);
                    break;
                }
                case(3):{
                    Armor a1 = Armor(classMod + " Chestpiece", "Chestpiece", mod);
                    lootTable.push_back(&a1);
                    break;
                }
                case(4):{
                    Armor a1 = Armor(classMod + " Boots", "Boots", mod);
                    lootTable.push_back(&a1);
                    break;
                }
            }
            pull = RNGesus.Roll()/25;
            mod = RNGesus.Roll()/25;
            wildcard = RNGesus.Roll();
            if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 10;
                classMod = "Greatsword";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard = 1){
                    classMod = "Dagger";
                    mod += 1;
                }
                if (wildcard = 2){
                    classMod = "Mace";
                    mod += 2;
                }
                if (wildcard = 3){
                    classMod = "Shortsword";
                    mod += 3;
                }
            }
            Weapon w1 = Weapon(mod, classMod);
            lootTable.push_back(&w1);


        }
        case(2):{
            mod = RNGesus.Roll()/10;
            wildcard = RNGesus.Roll();
            if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard = 1){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard = 2){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard = 3){
                    classMod = "Iron";
                    mod += 5;
                }
            }
            Armor a1 = Armor(classMod + " Helmet", "Helmet", mod);
            lootTable.push_back(&a1);
            Armor a2 = Armor(classMod + " Pants", "Pants", mod);
            lootTable.push_back(&a2);
            Armor a3 = Armor(classMod + " Chestpiece", "Chestpiece", mod);
            lootTable.push_back(&a3);
            Armor a4 = Armor(classMod + " Boots", "Boots", mod);
            lootTable.push_back(&a4);
            }

        
        case(3):{
            //1 pieces of armor, 2 consumable, 1 weapon
            mod = RNGesus.Roll()/10;
            Consumable c1 = Consumable("Potion of Healing", mod);
            mod = RNGesus.Roll()/10;
            Consumable c2 = Consumable("Potion of Healing", mod);
            lootTable.push_back(&c2);
            pull = RNGesus.Roll()/25;
            mod = RNGesus.Roll()/10;
            wildcard = RNGesus.Roll();
            if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard = 1){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard = 2){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard = 3){
                    classMod = "Iron";
                    mod += 5;
                }
            }
            switch(pull){
                case(1):{
                    Armor a1 = Armor(classMod + " Helmet", "Helmet", mod);
                    lootTable.push_back(&a1);
                    break;
                }
                case(2):{
                    Armor a1 = Armor(classMod + " Pants", "Pants", mod);
                    lootTable.push_back(&a1);
                    break;
                }
                case(3):{
                    Armor a1 = Armor(classMod + " Chestpiece", "Chestpiece", mod);
                    lootTable.push_back(&a1);
                    break;
                }
                case(4):{
                    Armor a1 = Armor(classMod + " Boots", "Boots", mod);
                    lootTable.push_back(&a1);
                    break;
                }
            }
            pull = RNGesus.Roll()/25;
            mod = RNGesus.Roll()/25;
            wildcard = RNGesus.Roll();
            if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 10;
                classMod = "Greatsword";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard = 1){
                    classMod = "Dagger";
                    mod += 1;
                }
                if (wildcard = 2){
                    classMod = "Mace";
                    mod += 2;
                }
                if (wildcard = 3){
                    classMod = "Shortsword";
                    mod += 3;
                }
            }
            Weapon w1 = Weapon(mod, classMod);
            lootTable.push_back(&w1);
        }
        case(4):{
            //1 weapon, 1 consumable
            pull = RNGesus.Roll()/25;
            mod = RNGesus.Roll()/25;
            wildcard = RNGesus.Roll();
            if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 10;
                classMod = "Greatsword";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard = 1){
                    classMod = "Dagger";
                    mod += 1;
                }
                if (wildcard = 2){
                    classMod = "Mace";
                    mod += 2;
                }
                if (wildcard = 3){
                    classMod = "Shortsword";
                    mod += 3;
                }
            }
            Weapon w1 = Weapon(mod, classMod);
            lootTable.push_back(&w1);
            mod = RNGesus.Roll()/10;
            Consumable c1 = Consumable("Potion of Healing", mod);
        }
        case(5):{
            //1 armor, 1 consumable
            mod = RNGesus.Roll()/10;
            Consumable c1 = Consumable("Potion of Healing", mod);
            lootTable.push_back(&c1);
            pull = RNGesus.Roll()/25;
            mod = RNGesus.Roll()/10;
            wildcard = RNGesus.Roll();
            if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard = 1){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard = 2){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard = 3){
                    classMod = "Iron";
                    mod += 5;
                }
            }
            switch(pull){
                case(1):{
                    Armor a1 = Armor(classMod + " Helmet", "Helmet", mod);
                    lootTable.push_back(&a1);
                    break;
                }
                case(2):{
                    Armor a1 = Armor(classMod + " Pants", "Pants", mod);
                    lootTable.push_back(&a1);
                    break;
                }
                case(3):{
                    Armor a1 = Armor(classMod + " Chestpiece", "Chestpiece", mod);
                    lootTable.push_back(&a1);
                    break;
                }
                case(4):{
                    Armor a1 = Armor(classMod + " Boots", "Boots", mod);
                    lootTable.push_back(&a1);
                    break;
                }
            }
        }
    }
    
}



Item* Loot::generateWeapon(){
        Dice RNGesus = Dice(100);
        int pull = RNGesus.Roll()/25;
        int mod = RNGesus.Roll()/25;
        int wildcard = RNGesus.Roll();
        std::string classMod;
        if (wildcard == 100){
            //1 in 100 chance of pulling super good gear
            mod += 10;
            classMod = "Greatsword";
            }
        else{
            wildcard = wildcard/33;
            if (wildcard = 1){
                classMod = "Dagger";
                mod += 1;
            }
            if (wildcard = 2){
                classMod = "Mace";
                mod += 2;
            }
            if (wildcard = 3){
                classMod = "Shortsword";
                mod += 3;
            }
            }
            Weapon w1 = Weapon(mod, classMod);
            return &w1;
}

Item* Loot::generateHelmet(){
        Dice RNGesus = Dice(100);
        int pull = RNGesus.Roll()/25;
        int mod = RNGesus.Roll()/25;
        int wildcard = RNGesus.Roll();
        std::string classMod;
        if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard = 1){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard = 2){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard = 3){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor a1 = Armor(classMod + " Helmet", "Helmet", mod);
        return &a1;
}
Item* Loot::generateChestplate(){
        Dice RNGesus = Dice(100);
        int pull = RNGesus.Roll()/25;
        int mod = RNGesus.Roll()/25;
        int wildcard = RNGesus.Roll();
        std::string classMod;
        if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard = 1){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard = 2){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard = 3){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor a1 = Armor(classMod + " Chestpiece", "Chestpiece", mod);
        return &a1;
                    

}
Item* Loot::generatePants(){
        Dice RNGesus = Dice(100);
        int pull = RNGesus.Roll()/25;
        int mod = RNGesus.Roll()/25;
        int wildcard = RNGesus.Roll();
        std::string classMod;
        if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard = 1){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard = 2){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard = 3){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor a1 = Armor(classMod + " Pants", "Pants", mod);
        return &a1;

}
Item* Loot::generateBoots(){
        Dice RNGesus = Dice(100);
        int pull = RNGesus.Roll()/25;
        int mod = RNGesus.Roll()/25;
        int wildcard = RNGesus.Roll();
        std::string classMod;
        if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard = 1){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard = 2){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard = 3){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor a1 = Armor(classMod + " Boots", "Boots", mod);
        return &a1;

}

