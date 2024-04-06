#include "Enemy.h"
#include "Corpse.h"
#include "../Map/Map.h"




Enemy::Enemy() {
    Dice coinflip = Dice(2);
    std::vector<Item*> inventory;

    inventory.push_back(Loot::generateWeapon());
    equippedWeapon = dynamic_cast<Weapon*>(inventory[0]);


    inventory.push_back(Loot::generateChestplate());
    equippedChestplate = dynamic_cast<Armor*>(inventory[1]);

    inventory.push_back(Loot::generateBoots());
    equippedBoots = dynamic_cast<Armor*>(inventory[2]);


    if (coinflip.Roll() == 2) {
        inventory.push_back(Loot::generatePants());
        equippedPants = dynamic_cast<Armor*>(inventory.back());
    } else {
        Armor* b1 = new Armor("Tattered Pants", "Pants", 1);
        inventory.push_back(b1);
        equippedPants = b1;
    }

    if (coinflip.Roll() == 2) {
        inventory.push_back(Loot::generateHelmet());
        equippedHelmet = dynamic_cast<Armor*>(inventory.back()); 
    } else {
        equippedHelmet = nullptr;
    }

    Dice lvl = Dice(5);
    level = lvl.Roll();
    maxHP = 5 + level;
    currentHP = maxHP;

    Dice speciesDice = Dice(5);
    std::string races[] = {"Goblin", "Human", "Orc", "Elf", "Dwarf"};
    name = races[speciesDice.Roll()];
}


std::string Enemy::status(){
    return "\n" + name + ": " + std::to_string(currentHP) + "/" + std::to_string(maxHP);
}

Corpse Enemy::kill(){
    return Corpse(this);
}
void Enemy::playerFlee(){
    currentHP = maxHP;
}

int Enemy::Attack(float modifier){
    int damage = (modifier * ((equippedWeapon->getDamage()))/2);
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
    currentHP -= damage;
    if (currentHP <= 0){
        std::cout << "\n" << name << " slain";
        alive = false;
    }
}



int Enemy::getX(){
	return xLocation;
}

int Enemy::getY(){
	return yLocation;
}

void Enemy::setX(int x){
    xLocation = x;
}

void Enemy::setY(int y){
	yLocation = y;
}


// TODO: Flesh out moveTo function
bool Enemy::moveTo(int x, int y, Map* map){
	if (map->getCell(x, y).type == EMPTY){
	    map->setCell(xLocation, yLocation, EMPTY);
	    map->setCell(x, y, OCCUPIED);
	    xLocation = x;
	    yLocation = y;
	    return true;
	}
	return false;
}
