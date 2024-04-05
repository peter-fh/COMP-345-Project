#include "Enemy.h"




Enemy::Enemy(){
    //Random
    std::vector<Item*> inventory;
    inventory.push_back(Loot::generateWeapon());
    equippedWeapon = dynamic_cast<Weapon*>(inventory[0]);
    inventory.push_back(Loot::generateChestplate());
    equippedChestplate = dynamic_cast<Armor*>(inventory[1]);
    inventory.push_back(Loot::generateBoots());
    equippedBoots = dynamic_cast<Armor*>(inventory[2]);

    Dice coinflip = Dice(2);
    if (coinflip.Roll() == 2){
        inventory.push_back(Loot::generatePants());
        equippedBoots = dynamic_cast<Armor*>(inventory[2]);
    }
    else{
        Armor b1 = Armor("Tatterred Pants", "Pants", 1);
        inventory.push_back(&b1);

    }
    if (coinflip.Roll() == 2){
        inventory.push_back(Loot::generateHelmet());
        equippedBoots = dynamic_cast<Armor*>(inventory[2]);
    }
    else{
        equippedHelmet = nullptr;
    }

    //ADJUST HP Here
    Dice HPMax = Dice(5);
    maxHP = 20 + HPMax.Roll();

    Dice species = Dice(5);
    //just giving some variety to enemy
    std::string races[] = {"Goblin", "Human", "Orc", "Elf", "Dwarf"};
    name = races[species.Roll()];
}

std::string Enemy::status(){
    return name + ": " + std::to_string(currentHP) + "/" + std::to_string(maxHP);
}

void takeDamage(){

}

Corpse Enemy::kill(){
    alive = false;
    return Corpse(this);
}
void Enemy::playerFlee(){
    currentHP = maxHP;
}

int Enemy::Attack(float modifier){
    int damage = (modifier * ((equippedWeapon->getDamage())/5));
    std::cout << "\n" << name << "attacked for " + std::to_string(damage) + " damage!";
    return damage;
}

void Enemy::takeDamage(int damage){
    currentHP -= damage;
    if (currentHP <= 0){
        std::cout << "\n" << name << " slain";
    }
}
