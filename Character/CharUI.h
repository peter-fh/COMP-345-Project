#pragma once
#include "../Observer/Observer.h"
#include "Character.h"
#include <iostream>
#include <string>

class CharUI : public Observer {
  private:
    Character* playerChar;
  
  public:
    std::string name;
    CharUI(Character* c);
    CharUI(Character* c, std::string name);
    void Update(std::string attribute, int newValue, int oldValue) override;
    void Update(Subject* subject) override;
    void Update(std::string message) override;
  
    void checkAbilityScores();
    void checkAttributes();
    void checkEquipment();
    void checkInventory();
    void nameCharacter();
    void statChecker();
    void regDisplay();
    void startup();
    void saveCharacter();
    void loadCharacter();
    void editorLoop();
    
    
    };

