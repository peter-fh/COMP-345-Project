class CharGUI{
  public:
    void checkAbilityScores();
    void checkAttributes();
    void checkEquipment();
    void nameCharacter();
    void setLast();

  private:
    string name;
    //reused some code from Eric Lui below, thank you

    int lastLevel; // assigned at the beginning
    int lastHitPoints; // based on constitution modifier and level
    int lastArmorClass; // based on dexterity modifier
    int lastAttackBonus; // based level and strength/dexterity modifiers
    int lastDamageBonus; //based on strength modifier
    // ability score
    int lastStrength;
    int lastDexterity;
    int lastConstitution;
    int lastIntelligence;
    int lastWisdom;
    int lastCharisma;
    // ability modifier
    int lastStrengthMod;
    int lastDexterityMod;
    int lastConstitutionMod;
    int lastIntelligenceMod;
    int lastWisdomMod;
    int lastCharismaMod;
    // equipment
    string lastArmor;
    string lastShield;
    string lastWeapon;
    string lastBoots;
    string lastRing;
    string lastHelmet;
