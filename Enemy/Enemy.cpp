#include "Enemy.h"
#include "Corpse.h"



Enemy::Enemy(std::string givenName, int givenLevel, int givenHP, Weapon* weapon, Armor* Helmet, Armor* Chestplate, Armor* Pants, Armor* Boots){
    name = givenName;
    level = givenLevel;
    maxHP = givenHP;
    currentHP = givenHP;
    std::vector<Item*> inventory;
    armorMod = 0;
    equippedWeapon = weapon;
    inventory.push_back(weapon);
    equippedHelmet = Helmet;
    inventory.push_back(Helmet);
    armorMod += Helmet->getDefence();
    equippedChestplate = Chestplate;
    inventory.push_back(Chestplate);
    armorMod += Chestplate->getDefence();
    equippedPants = Pants;
    inventory.push_back(Pants);
    armorMod += Pants->getDefence();
    equippedBoots = Boots;
    inventory.push_back(Boots);
    armorMod += Boots->getDefence();
}

void Enemy::giveItem(Item* i){
    inventory.push_back(i);
}
Enemy::Enemy(std::string nom, int lvl, bool friends){
    name = nom;
    level = lvl;
    friendly = friends;
    maxHP = 5 + lvl;
    currentHP = 5 + lvl;
    std::vector<Item*> inventory;
    int armorMod = 0;
    Dice coinflip = Dice(2);
    
    inventory.push_back(Loot::generateWeapon());
    equippedWeapon = dynamic_cast<Weapon*>(inventory[0]);


    inventory.push_back(Loot::generateChestplate());
    equippedChestplate = dynamic_cast<Armor*>(inventory[1]);
    armorMod += equippedChestplate->getDefence();

    inventory.push_back(Loot::generateBoots());
    equippedBoots = dynamic_cast<Armor*>(inventory[2]);
    armorMod += equippedBoots->getDefence();


    if (coinflip.Roll() == 2) {
        inventory.push_back(Loot::generatePants());
        equippedPants = dynamic_cast<Armor*>(inventory.back());
        armorMod += equippedPants->getDefence();
    } else {
        Armor* b1 = new Armor("Tattered Pants", "Pants", 1);
        inventory.push_back(b1);
        equippedPants = b1;
        armorMod += 1;
    }

    if (coinflip.Roll() == 2) {
        inventory.push_back(Loot::generateHelmet());
        equippedHelmet = dynamic_cast<Armor*>(inventory.back()); 
        armorMod += equippedHelmet->getDefence();
    } else {
        equippedHelmet = nullptr;
    }
}

Enemy::Enemy() {
    friendly = false;
    Dice coinflip = Dice(2);
    std::vector<Item*> inventory;
    int armorMod = 0;

    inventory.push_back(Loot::generateWeapon());
    equippedWeapon = dynamic_cast<Weapon*>(inventory[0]);


    inventory.push_back(Loot::generateChestplate());
    equippedChestplate = dynamic_cast<Armor*>(inventory[1]);
    armorMod += equippedChestplate->getDefence();

    inventory.push_back(Loot::generateBoots());
    equippedBoots = dynamic_cast<Armor*>(inventory[2]);
    armorMod += equippedBoots->getDefence();


    if (coinflip.Roll() == 2) {
        inventory.push_back(Loot::generatePants());
        equippedPants = dynamic_cast<Armor*>(inventory.back());
        armorMod += equippedPants->getDefence();
    } else {
        Armor* b1 = new Armor("Tattered Pants", "Pants", 1);
        inventory.push_back(b1);
        equippedPants = b1;
        armorMod += 1;
    }

    if (coinflip.Roll() == 2) {
        inventory.push_back(Loot::generateHelmet());
        equippedHelmet = dynamic_cast<Armor*>(inventory.back()); 
        armorMod += equippedHelmet->getDefence();
    } else {
        equippedHelmet = nullptr;
    }

    Dice lvl = Dice(5);
    level = lvl.Roll();
    maxHP = 5 + level;
    currentHP = maxHP;

    Dice speciesDice = Dice(5);
    std::string races[] = {"Goblin", "Human", "Orc", "Elf", "Dwarf"};
    name = races[speciesDice.Roll() - 1];
}


std::string Enemy::status(){
    return "\n" + name + ": " + std::to_string(currentHP) + "/" + std::to_string(maxHP);
}

void Enemy::kill(){
    new Corpse(this);
}
void Enemy::playerFlee(){
    currentHP = maxHP;
}

int Enemy::Attack(float modifier){
    int damage = (modifier * ((equippedWeapon->getDamage())));
    if (damage == 0){
        std::cout << "\nAttack missed";
    }
    else{
        std::cout << "\n" << name << " attacked for " + std::to_string(damage) + " damage!\n";
    }
    return damage;
}
void Enemy::equipment(){
    std::cout << "Equipment\n" << equippedWeapon->getItemName()  << "\n";
    if (equippedHelmet != nullptr){
        std::cout << equippedHelmet->getItemName() << "\n";
    }
    std::cout << equippedChestplate->getItemName() << "\n" << equippedPants->getItemName() << "\n" << equippedBoots->getItemName();
}

void Enemy::takeDamage(int damage){
    int blocked = 0;
    armorMod = 0;
    if (armorMod > 10){
	    damage -= armorMod/10;
	    currentHP -= damage;
	    blocked = armorMod/10;
    }
    else{
	    currentHP -= damage;
    }
    if (blocked > 0){
        std::cout << "Armor blocks " << blocked << " damage";
    }
    if (currentHP <= 0){
        std::cout << "\n" << name << " slain";
        alive = false;
    }
}

void Enemy::determineSymbol(){
    this->setSymbol('E');
}
