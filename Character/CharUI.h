#include "../Observer/Observer.h"
#include "Character.h"
#include <iostream>
#include <string>

class CharUI : public Observer {
  public:
    CharUI(Character* c);
    void Update(string attribute, int newValue, int oldValue) override;
    void checkAbilityScores();
    void checkAttributes();
    void checkEquipment();
    void nameCharacter();
    void setLast();
    void statChecker();

  private:
    string name;
    Character* char;
