#include "Loot.h"
#include <fstream>
#include <iostream>

std::vector<Item*> Loot::generateChestLoot(){
    Dice RNGesus2 = Dice(5);
    Dice RNGesus = Dice(100);
    int table = RNGesus2.Roll();
    std::vector<Item*> lootTable;
    int pull, mod, wildcard;
    std::string classMod;
    std::ofstream outfile("loot_debug.txt");
    outfile << "Table: " << table << std::endl;
    switch(table){
        case(1):{
            //1 weapon, 1 random armor piece, 1 consumable
            mod = RNGesus.Roll()/10;
            Consumable* c1 = new Consumable("Potion of Healing", mod);
            lootTable.push_back(c1);
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
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
            switch(pull){
                case(1):{
                    Armor* a1 = new Armor(classMod + " Helmet", "Helmet", mod);
                    lootTable.push_back(a1);
                    break;
                }
                case(2):{
                    Armor* a1 = new Armor(classMod + " Pants", "Pants", mod);
                    lootTable.push_back(a1);
                    break;
                }
                case(3):{
                    Armor* a1 = new Armor(classMod + " Chestpiece", "Chestpiece", mod);
                    lootTable.push_back(a1);
                    break;
                }
                case(4):{
                    Armor* a1 = new Armor(classMod + " Boots", "Boots", mod);
                    lootTable.push_back(a1);
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
                if (wildcard == 0){
                    classMod = "Dagger";
                    mod += 1;
                }
                if (wildcard == 1){
                    classMod = "Mace";
                    mod += 2;
                }
                if (wildcard == 2){
                    classMod = "Shortsword";
                    mod += 3;
                }
            }
            Weapon* w1 = new Weapon(mod, classMod);
            lootTable.push_back(w1);
            break;
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
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
            Armor* a1 = new Armor(classMod + " Helmet", "Helmet", mod);
            lootTable.push_back(a1);
            Armor* a2 = new Armor(classMod + " Pants", "Pants", mod);
            lootTable.push_back(a2);
            Armor* a3 = new Armor(classMod + " Chestpiece", "Chestpiece", mod);
            lootTable.push_back(a3);
            Armor* a4 = new Armor(classMod + " Boots", "Boots", mod);
            lootTable.push_back(a4);
            break;
            }

        
        case(3):{
            //1 pieces of armor, 2 consumable, 1 weapon
            mod = RNGesus.Roll()/10;
            Consumable* c1 = new Consumable("Potion of Healing", mod);
            mod = RNGesus.Roll()/10;
            Consumable* c2 = new Consumable("Potion of Healing", mod);
            lootTable.push_back(c2);
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
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
            switch(pull){
                case(1):{
                    Armor* a1 = new Armor(classMod + " Helmet", "Helmet", mod);
                    lootTable.push_back(a1);
                    break;
                }
                case(2):{
                    Armor* a1 = new Armor(classMod + " Pants", "Pants", mod);
                    lootTable.push_back(a1);
                    break;
                }
                case(3):{
                    Armor* a1 = new Armor(classMod + " Chestpiece", "Chestpiece", mod);
                    lootTable.push_back(a1);
                    break;
                }
                case(4):{
                    Armor* a1 = new Armor(classMod + " Boots", "Boots", mod);
                    lootTable.push_back(a1);
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
                if (wildcard == 0){
                    classMod = "Dagger";
                    mod += 1;
                }
                if (wildcard == 1){
                    classMod = "Mace";
                    mod += 2;
                }
                if (wildcard == 2){
                    classMod = "Shortsword";
                    mod += 3;
                }
            }
            Weapon* w1 = new Weapon(mod, classMod);
            lootTable.push_back(w1);
            break;
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
                if (wildcard == 0){
                    classMod = "Dagger";
                    mod += 1;
                }
                if (wildcard == 1){
                    classMod = "Mace";
                    mod += 2;
                }
                if (wildcard == 2){
                    classMod = "Shortsword";
                    mod += 3;
                }
            }
            Weapon* w1 = new Weapon(mod, classMod);
            lootTable.push_back(w1);
            mod = RNGesus.Roll()/10;
            Consumable *c1 = new Consumable("Potion of Healing", mod);
            break;
        }
        case(5):{
            //1 armor, 1 consumable
            mod = RNGesus.Roll()/10;
            Consumable* c1 = new Consumable("Potion of Healing", mod);
            lootTable.push_back(c1);
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
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
            switch(pull){
                case(1):{
                    Armor* a1 = new Armor(classMod + " Helmet", "Helmet", mod);
                    lootTable.push_back(a1);
                    break;
                }
                case(2):{
                    Armor* a1 = new Armor(classMod + " Pants", "Pants", mod);
                    lootTable.push_back(a1);
                    break;
                }
                case(3):{
                    Armor* a1 = new Armor(classMod + " Chestpiece", "Chestpiece", mod);
                    lootTable.push_back(a1);
                    break;
                }
                case(4):{
                    Armor* a1 = new Armor(classMod + " Boots", "Boots", mod);
                    lootTable.push_back(a1);
                    break;
                }
            }
            break;
        }
    }
    return lootTable;
    
}



Item* Loot::generateWeapon(){
        Dice RNGesus = Dice(100);
        int pull = RNGesus.Roll()/25;
        int mod = RNGesus.Roll()/25 + 1;
        int wildcard = RNGesus.Roll();
        std::string classMod;
        if (wildcard == 100){
            //1 in 100 chance of pulling super good gear
            mod += 10;
            classMod = "Greatsword";
            }
        else{
            wildcard = wildcard/33;
            if (wildcard == 0){
                classMod = "Dagger";
                mod += 1;
            }
            if (wildcard == 1){
                classMod = "Mace";
                mod += 2;
            }
            if (wildcard == 2){
                classMod = "Shortsword";
                mod += 3;
            }
            }
            Weapon* w1 = new Weapon(mod, classMod);
            return w1;
}

Item* Loot::generateWeapon(int i){
        Dice RNGesus = Dice(100);
        int pull = i/25;
        int mod = i/25 + 1;
        int wildcard = i;
        std::string classMod;
        if (wildcard == 100){
            //1 in 100 chance of pulling super good gear
            mod += 10;
            classMod = "Greatsword";
            }
        else{
            wildcard = wildcard/33;
            if (wildcard == 0){
                classMod = "Dagger";
                mod += 1;
            }
            if (wildcard == 1){
                classMod = "Mace";
                mod += 2;
            }
            if (wildcard == 2){
                classMod = "Shortsword";
                mod += 3;
            }
            }
            Weapon* w1 = new Weapon(mod, classMod);
            return w1;
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
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor* a1 = new Armor(classMod + " Helmet", "Helmet", mod);
        return a1;
}
Item* Loot::generateHelmet(int i){
        int pull = i/25;
        int mod = i/25;
        int wildcard = i;
        std::string classMod;
        if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor* a1 = new Armor(classMod + " Helmet", "Helmet", mod);
        return a1;
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
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor* a1 = new Armor(classMod + " Chestpiece", "Chestpiece", mod);
        return a1;
                    

}
Item* Loot::generateChestplate(int i){
        int pull = i/25;
        int mod = i/25;
        int wildcard = i;
        std::string classMod;
        if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor* a1 = new Armor(classMod + " Chestpiece", "Chestpiece", mod);
        return a1;
                    

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
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor* a1 = new Armor(classMod + " Pants", "Pants", mod);
        return a1;

}
Item* Loot::generatePants(int i){
        int pull = i/25;
        int mod = i/25;
        int wildcard = i;
        std::string classMod;
        if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor* a1 = new Armor(classMod + " Pants", "Pants", mod);
        return a1;

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
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor* a1 = new Armor(classMod + " Boots", "Boots", mod);
        return a1;

}

Item* Loot::generateBoots(int i){
        int pull = i/25;
        int mod = i/25;
        int wildcard = i;
        std::string classMod;
        if (wildcard == 100){
                //1 in 100 chance of pulling super good gear
                mod += 20;
                classMod = "Diamond";
            }
            else{
                wildcard = wildcard/33;
                if (wildcard == 0){
                    classMod = "Leather";
                    mod += 3;
                }
                if (wildcard == 1){
                    classMod = "Chainmail";
                    mod += 4;
                }
                if (wildcard == 2){
                    classMod = "Iron";
                    mod += 5;
                }
            }
        Armor* a1 = new Armor(classMod + " Boots", "Boots", mod);
        return a1;

}

