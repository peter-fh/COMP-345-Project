#include "CharUI.h"

/* Jackson Abbott 40252068
Character UI/observer, attaches to character, displays stats, notifies of changes

*/
CharUI::CharUI(Character* c) : playerChar(c){
            if (playerChar) {
                  playerChar->Attach(this);
                        
                  //nameCharacter();
                  regDisplay();
                  statChecker();
            }
            else{
                  std::cout << "Failed attachment, please pass a reference to a character";
      }
}

void CharUI::checkInventory(){
      std::cout << playerChar->getName() << "'s inventory!\n";
      playerChar->inventoryCheck();
}

CharUI::CharUI(Character* c, std::string given) : playerChar(c){
            if (playerChar) {
                        playerChar->Attach(this);
                        setName(given);
            }
            else{
                        std::cout << "Failed attachment, please pass a reference to a character";   
            }

}


void CharUI::Update(std::string attribute, int newValue, int oldValue) {
    std::cout << "\nUpdate: " << attribute << " changed from " << newValue << " to " << oldValue;
}

void CharUI::Update(Subject* subject){
    
}

void CharUI::setName(std::string given){
            name = given;
}

void CharUI::statChecker(){
      std::string selection, again;
      std::cout << "Check stats? (y/n): ";
      std::std::getline(cin, selection);
      if (selection != "y" && selection != "Y" && selection != "n" && selection != "N"){ 
            do{
                  std::cout << "\nInvalid, please try again";
                  std::cout << "\nCheck stats? (y/n): ";
                  std::std::getline(cin, selection);
            } while (selection != "y" && selection != "Y" && selection != "n" && selection != "N");
                  }
      if (selection == "y" || selection == "Y"){
            do{
                  selection = "";
                  again = "";
                  std::cout << "Options\n \t1 - Check Attributes\n \t2 - Check Ability Scores\n \t3 - Check Equipment";
                  std::getline(cin, selection);
                  if (selection != "1" && selection != "2" && selection != "3" && selection != "N"){ 
                  do{
                        std::cout << "\nInvalid, please try again";
                        std::cout << "Options\n \t1 - Check Attributes\n \t2 - Check Ability Scores\n \t3 - Check Equipment";
                        std::getline(cin, selection);
                  } while (selection != "1" && selection != "2" && selection != "3");
                  }
                  if (selection == "1") checkAttributes();
                  if (selection == "2") checkAbilityScores();
                  if (selection == "3") checkEquipment();
                  std::cout << "Check another? (y/n): ";
                  std::getline(cin, again);
                  if (again != "y" && again != "Y" && again != "n" && again != "N"){ 
                        do{
                              std::cout << "\nInvalid, please try again";
                              std::cout << "\nCheck another? (y/n): ";
                              std::getline(cin, again);
                        } while (again != "y" && again != "Y" && again != "n" && again != "N");
                  }
            }while (again == "y" || again =="Y");
                  }
}

void CharUI::nameCharacter() {
    std::cout << "Please enter your character's name: ";
    std::getline(cin, CharUI::name);
    std::string selection = "n";
    do {
        std::cout << "\nYou selected \"" << name << "\", is this correct? It cannot be changed later (y/n): ";
        std::getline(cin, selection);
        // Assuming a strip() function exists or similar logic is implemented to trim whitespace
        if (selection == "y" || selection == "Y") break;
        else if (selection == "n" || selection == "N") {
            std::cout << "\nPlease enter your character's name: ";
            std::getline(cin, name);
        }
        else {
            std::cout << "\nInvalid entry, please try again (y/n):";
        }
    } while (selection != "Y" && selection != "y");
}

  void CharUI::regDisplay(){
    std::cout << "  Name:" << CharUI::name + "\n";
    std::cout << "  Level: " << playerChar->getLevel() << "\n";
    std::cout << "  Hit Points: " << playerChar->getHitPoints() << "\n";
  }
  void CharUI::checkAbilityScores(){
    std::cout << "  Strength: " << playerChar->getStrength() << " (Mod: " << playerChar->getStrengthMod() << ")" << "\n";
    std::cout << "  Dexterity: " << playerChar->getDexterity() << " (Mod: " << playerChar->getDexterityMod() << ")" << "\n";
    std::cout << "  Constitution: " << playerChar->getConstitution() << " (Mod: " << playerChar->getConstitutionMod() << ")" << "\n";
    std::cout << "  Intelligence: " << playerChar->getIntelligence() << " (Mod: " << playerChar->getIntelligenceMod() << ")" << "\n";
    std::cout << "  Wisdom: " << playerChar->getWisdom() << " (Mod: " << playerChar->getWisdomMod() << ")" << "\n";
    std::cout << "  Charisma: " << playerChar->getCharisma() << " (Mod: " << playerChar->getCharismaMod() << ")" << "\n";
    }
  void CharUI::checkAttributes(){
    std::cout << "Level: " << playerChar->getLevel() << "\n";
    std::cout << "Hit Points: " << playerChar->getHitPoints() << "\n";
    std::cout << "Armor Class: " << playerChar->getArmorClass() << "\n";
    std::cout << "Attack Bonus: " << playerChar->getAttackBonus() << "\n";
    std::cout << "Damage Bonus: " << playerChar->getDamageBonus() << "\n";
  }
  void CharUI::checkEquipment(){
    std::cout << "  Armor: " << (playerChar->getArmor().empty() ? "None" : playerChar->getArmor()) << "\n";
    std::cout << "  Shield: " << (playerChar->getShield().empty() ? "None" : playerChar->getShield()) << "\n";
    std::cout << "  Weapon: " << (playerChar->getWeapon().empty() ? "None" : playerChar->getWeapon()) << "\n";
    std::cout << "  Boots: " << (playerChar->getBoots().empty() ? "None" : playerChar->getBoots()) << "\n";
    std::cout << "  Ring: " << (playerChar->getRing().empty() ? "None" : playerChar->getRing()) << "\n";
    std::cout << "  Helmet: " << (playerChar->getHelmet().empty() ? "None" : playerChar->getHelmet()) << "\n";
  }
