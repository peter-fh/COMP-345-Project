#include <iostream>
#include <string>
#include "Character/Character.h"
using namespace std;

class CharGUI: public Character {
  String name;

  void checkAbilityScores{
    cout << "  Strength: " << getStrength() << " (Mod: " << getStrengthMod() << ")" << "\n";
    cout << "  Dexterity: " << getDexterity() << " (Mod: " << getDexterityMod() << ")" << "\n";
    cout << "  Constitution: " << getConstitution() << " (Mod: " << getConstitutionMod() << ")" << "\n";
    cout << "  Intelligence: " << getIntelligence() << " (Mod: " << getIntelligenceMod() << ")" << "\n";
    cout << "  Wisdom: " << getWisdom() << " (Mod: " << getWisdomMod() << ")" << "\n";
    cout << "  Charisma: " << getCharisma() << " (Mod: " << getCharismaMod() << ")" << "\n";
    }
  void checkAttributes{
    cout << "Level: " << getLevel() << "\n";
    cout << "Hit Points: " << getHitPoints() << "\n";
    cout << "Armor Class: " << getArmorClass() << "\n";
    cout << "Attack Bonus: " << getAttackBonus() << "\n";
    cout << "Damage Bonus: " << getDamageBonus() << "\n";
  }
  void checkEquipment{
    cout << "  Armor: " << (getArmor().empty() ? "None" : getArmor()) << "\n";
    cout << "  Shield: " << (getShield().empty() ? "None" : getShield()) << "\n";
    cout << "  Weapon: " << (getWeapon().empty() ? "None" : getWeapon()) << "\n";
    cout << "  Boots: " << (getBoots().empty() ? "None" : getBoots()) << "\n";
    cout << "  Ring: " << (getRing().empty() ? "None" : getRing()) << "\n";
    cout << "  Helmet: " << (getHelmet().empty() ? "None" : getHelmet()) << "\n";
  }
  void nameCharacter(){
    //self explainatory, names character when called, verifies it is the intended name
    cout << "Please enter your characters name:";
    getline(cin, name);
    string selection = 'n';
    do{
      cout << "\nYou selected \"" << name << "\", is this correct? It cannot be changed later (y/n)";
      getline(cin, selection);
      selection.strip();
      if (selection == "y" || selection =="Y") break;
      else{
        if (selection == "n" || selection == "N"){
          cout << "\nPlease enter your characters name:";
          getline(cin, name);
        }
        else while (selection != "n" && selection != "N" && selection != "Y" && selection != "y"){
          cout << "\nInvalid entry, please try again (y/n):";
          getline(cin, selection);
          selection.strip();
        }
      }
      } while (selection != "Y" && selection != "y");
  }
    

  void regDisplay(){
    cout << "  Name:" << name;
    cout << "Level: " << getLevel() << "\n";
    cout << "Hit Points: " << getHitPoints() << "\n";
  }

  CharGUI(Character c){
    nameCharacter();
    regDisplay();
    char selection;

    
    
    while char
    
    
}

