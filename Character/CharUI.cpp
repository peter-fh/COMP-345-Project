#include "CharUI.h"

CharUI::CharUI(Character* c) : character(c){
      if (character) {
        character->Attach(this);
    }
    nameCharacter();
    regDisplay();
    statChecker();
}


void CharUI::Update(const string& attribute, int newValue, int oldValue) {
    cout << "Update: " << attribute << " changed from " << oldValue << " to " << newValue;
}

void CharUI::statChecker(){
      string selection, again;
      cout << "Check stats? (y/n): ";
      getline(cin, selection);
      selection = selection.strip();
      if (selection != "y" && selection != "Y" && selection != "n" && selection != "N"){ 
            do{
                  cout << "\nInvalid, please try again"
                  cout << "\nCheck stats? (y/n): ";
                  getline(cin, selection);
            } while (selection != "y" && selection != "Y" && selection != "n" && selection != "N")
                  }
      if (selection == "y" || selection == "Y"){
            do{
                  selection = "";
                  again = "";
                  cout << "Options\n \t1 - Check Attributes\n \t2 - Check Ability Scores\n \t3 - Check Equipment";
                  getline(cin, selection);
                  selection = selection.strip();
                  if (selection != "1" && selection != "2" && selection != "3" && selection != "N"){ 
                  do{
                        cout << "\nInvalid, please try again"
                        cout << "Options\n \t1 - Check Attributes\n \t2 - Check Ability Scores\n \t3 - Check Equipment";
                        getline(cin, selection);
                        selection = selection.strip();
                  } while (selection != "1" && selection != "2" && selection != "3")
                  }
                  if (selection == "1") checkAttributes();
                  if (selection == "2") checkAbilityScores();
                  if (selection == "3") checkEquipment();
                  cout << "Check another? (y/n): ";
                  getline(cin, again);
                  again = again.strip();
                  if (again != "y" && again != "Y" && again != "n" && again != "N"){ 
                        do{
                              cout << "\nInvalid, please try again"
                              cout << "\nCheck another? (y/n): ";
                              getline(cin, again);
                        } while (again != "y" && again != "Y" && again != "n" && again != "N")
                  }
            }while (again == "y" || again =="Y")
                  }
}

void CharUI::nameCharacter() {
    cout << "Please enter your character's name: ";
    character->getline(cin, name);
    string selection = "n";
    do {
        cout << "\nYou selected \"" << name << "\", is this correct? It cannot be changed later (y/n): ";
        character->getline(cin, selection);
        // Assuming a strip() function exists or similar logic is implemented to trim whitespace
        if (selection == "y" || selection == "Y") break;
        else if (selection == "n" || selection == "N") {
            cout << "\nPlease enter your character's name: ";
            character->getline(cin, name);
        }
        else {
            cout << "\nInvalid entry, please try again (y/n):";
        }
    } while (selection != "Y" && selection != "y");
}
  void regDisplay(){
    cout << "  Name:" << name;
    cout << "Level: " << character->getLevel() << "\n";
    cout << "Hit Points: " << character->getHitPoints() << "\n";
  }
  void checkAbilityScores(){
    cout << "  Strength: " << character->getStrength() << " (Mod: " << character->getStrengthMod() << ")" << "\n";
    cout << "  Dexterity: " << character->getDexterity() << " (Mod: " << character->getDexterityMod() << ")" << "\n";
    cout << "  Constitution: " << character->getConstitution() << " (Mod: " << character->getConstitutionMod() << ")" << "\n";
    cout << "  Intelligence: " << character->getIntelligence() << " (Mod: " << character->getIntelligenceMod() << ")" << "\n";
    cout << "  Wisdom: " << character->getWisdom() << " (Mod: " << character->getWisdomMod() << ")" << "\n";
    cout << "  Charisma: " << character->getCharisma() << " (Mod: " << character->getCharismaMod() << ")" << "\n";
    }
  void checkAttributes(){
    cout << "Level: " << character->getLevel() << "\n";
    cout << "Hit Points: " << character->getHitPoints() << "\n";
    cout << "Armor Class: " << character->getArmorClass() << "\n";
    cout << "Attack Bonus: " << character->getAttackBonus() << "\n";
    cout << "Damage Bonus: " << character->getDamageBonus() << "\n";
  }
  void checkEquipment(){
    cout << "  Armor: " << (getArmor().empty() ? "None" : character->getArmor()) << "\n";
    cout << "  Shield: " << (getShield().empty() ? "None" : character->getShield()) << "\n";
    cout << "  Weapon: " << (getWeapon().empty() ? "None" : character->getWeapon()) << "\n";
    cout << "  Boots: " << (getBoots().empty() ? "None" : character->getBoots()) << "\n";
    cout << "  Ring: " << (getRing().empty() ? "None" : character->getRing()) << "\n";
    cout << "  Helmet: " << (getHelmet().empty() ? "None" : character->getHelmet()) << "\n";
  }
