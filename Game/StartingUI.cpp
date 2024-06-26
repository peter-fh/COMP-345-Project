#include "StartingUI.h"


void StartingUI::CharacterBuilder(){
    std::string selection, name, dead;

    std::cout << "Please enter your character's name: ";
    std::getline(cin, name);

    cout << "Generating Armor";
    Dice d = Dice(20);
    int roll;
    do{
        selection = "";
        cout << "Roll";
        std::getline(cin, dead);
        roll = d.Roll();
        cout << "Rolled: " << roll;
        Weapon* weapon = dynamic_cast<Weapon*>(Loot::generateWeapon());
        cout << weapon->getItemName();
        cout << "Roll";
        std::getline(cin, dead);
        roll = d.Roll();
        cout << "Rolled: " << roll;
        Armor* helmet = dynamic_cast<Armor*>(Loot::generateHelmet());
        cout << helmet->getItemName();
        cout << "Roll";
        std::getline(cin, dead);
        roll = d.Roll();
        cout << "Rolled: " << roll;
        Armor* chestplate = dynamic_cast<Armor*>(Loot::generateChestplate());
        cout << chestplate->getItemName();
        cout << "Roll";
        std::getline(cin, dead);
        roll = d.Roll();
        cout << "Rolled: " << roll;
        Armor* pants = dynamic_cast<Armor*>(Loot::generatePants());
        cout << pants->getItemName();
        cout << "Roll";
        std::getline(cin, dead);
        roll = d.Roll();
        cout << "Rolled: " << roll;
        Armor* boots = dynamic_cast<Armor*>(Loot::generateBoots());
        cout << boots->getItemName();
        cout << "Roll";
        std::getline(cin, dead);
        roll = d.Roll();
        cout << "Rolled: " << roll;
        cout << "Reroll gear? (y/n)";
        std::getline(cin, selection);
    } while (selection != "N" || selection != "n");
    //push character to map and equip items

}

void StartingUI::NPCBuilder(){
    std::string name, level, friendly;
    cout << "\nEnter NPC Name: ";
    std::getline(cin, name);
    cout << "\nEnter NPC Level: ";
    std::getline(cin, level);
    int lvl = stoi(level);
    cout << "\nFriendly? (y/n)";
    std::getline(cin, friendly);
    while (friendly != "Y" && friendly != "y" && friendly != "N" && friendly != "n"){
        cout << "\nInvalid entry. Friendly? (y/n)";
        std::getline(cin, friendly);
    }
    if (friendly == "N" || friendly == "n"){
        new Enemy(name, lvl, true, nullptr, nullptr, nullptr, nullptr, nullptr);
        return;
    }
    else{
        new Enemy(name, lvl, true, nullptr, nullptr, nullptr, nullptr, nullptr);
        return;
    }
}

