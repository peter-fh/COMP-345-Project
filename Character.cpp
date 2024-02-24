#include <cstdlib> // For std::rand() and std::srand()
#include <ctime>   // For std::time()
#include <iostream>
#include <string>
#include <stdexcept>
#include <math.h>
#include <bits/stdc++.h>
#include "Character.h"
using namespace std;

Character::Character(int setLevel){
    if (setLevel > 0){
        level = setLevel;

        strength = generateAbilityScores();
        dexterity = generateAbilityScores();
        constitution = generateAbilityScores();
        intelligence = generateAbilityScores();
        wisdom = generateAbilityScores();
        charisma = generateAbilityScores();

        strengthMod = calculateModifiers(strength);
        dexterityMod = calculateModifiers(dexterity);
        constitutionMod = calculateModifiers(constitution);
        intelligenceMod = calculateModifiers(intelligence);
        wisdomMod = calculateModifiers(wisdom);
        charismaMod = calculateModifiers(charisma);

        hitPoints = calculateHitPoints();
        armorClass = calculateArmorClass();
        attackBonus = calculateAttackBonus();
        damageBonus = calculateDamageBonus();        
    }
    else{
        throw invalid_argument("Level must be positive");
    }
}
int Character::generateAbilityScores(){
    int n = 4;
    int roll[4];
    for (int i=0;i<n; i++){ // rolling 4d6
        int high = 6;
        int low = 1;
        roll[i] = rand() % (high - low) + low;
    }
    
    sort(roll, roll + n); // dropping the lowest roll
    return roll[1]+roll[2]+roll[3]; // summing the rest
}
int Character::calculateModifiers(int points){
    float difference = points-10;
    float modifier = difference/2;
    return floor(modifier);
}
int Character::calculateHitPoints(){
    return getConstitutionMod()+level;
}
int Character::calculateArmorClass(){
    return getDexterityMod();
}
int Character::calculateAttackBonus(){
    return level+getStrengthMod()+getDexterityMod();
}
int Character::calculateDamageBonus(){
    return getStrengthMod();
}
// Setter for level
void Character::setLevel(int newLevel){
    if (newLevel > 0){
        level = newLevel;
        recalculateAttributes();
    }
    else{
        throw invalid_argument("Level must be positive");
    }
}
void Character::setStrength(int newStrength){
    if (newStrength >= 0){
        strength = newStrength;
    } 
    else{
        throw invalid_argument("Strength must be positive");
    }
}
void Character::setDexterity(int newDexterity){
    if (newDexterity >= 0){
        dexterity = newDexterity;
    }
    else{
        throw invalid_argument("Dexterity must be positive");
    }
}
void Character::setConstitution(int newConstitution){
    if (newConstitution >= 0){
        constitution = newConstitution;
    }
    else{
        throw invalid_argument("Constitution must be positive");
    }
}
void Character::setIntelligence(int newIntelligence){
    if (newIntelligence >= 0){
        intelligence = newIntelligence;
    }
    else{
        throw invalid_argument("Intelligence must be positive");
    }
}
void Character::setWisdom(int newWisdom){
    if (newWisdom >= 0){
        wisdom = newWisdom;
    }
    else{
        throw invalid_argument("Wisdom must be positive");
    }
}
void Character::setCharisma(int newCharisma){
    if (newCharisma >= 0){
        charisma = newCharisma;
    }
    else{
        throw invalid_argument("Charisma must be positive");
    }
}
//increase (buff and debuff)
void Character::increaseLevel(int levelUp){
    if (level+levelUp > 0){
        level+=levelUp;
        recalculateAttributes();
    }
    else{
        throw invalid_argument("New Level must be positive");
    }
}
void Character::increaseStrength(int buffStrength){
    if (strength + buffStrength >= 0){
        strength += buffStrength;
        strengthMod = calculateModifiers(strength);
        recalculateAttributes();
    } 
    else{
        throw invalid_argument("New Strength must be positive");
    }
}
void Character::increaseDexterity(int buffDexterity){
    if (dexterity + buffDexterity >= 0){
        dexterity += buffDexterity;
        dexterityMod = calculateModifiers(dexterity);
        recalculateAttributes();
    }
    else{
        throw invalid_argument("New Dexterity must be positive");
    }
}
void Character::increaseConstitution(int buffConstitution){
    if (constitution + buffConstitution >= 0){
        constitution += buffConstitution;
        constitutionMod = calculateModifiers(constitution);
        recalculateAttributes();
    }
    else{
        throw invalid_argument("New Constitution must be positive");
    }
}
void Character::increaseIntelligence(int buffIntelligence){
    if (intelligence + buffIntelligence >= 0){
        intelligence += buffIntelligence;
        intelligenceMod = calculateModifiers(intelligence);
        recalculateAttributes();
    }
    else{
        throw invalid_argument("New Intelligence must be positive");
    }
}
void Character::increaseWisdom(int buffWisdom){
    if (wisdom + buffWisdom >= 0){
        wisdom += buffWisdom;
        wisdomMod = calculateModifiers(wisdom);
        recalculateAttributes();
    }
    else{
        throw invalid_argument("New Wisdom must be positive");
    }
}
void Character::increaseCharisma(int buffCharisma){
    if (charisma + buffCharisma >= 0){
        charisma += buffCharisma;
        charismaMod = calculateModifiers(charisma);
        recalculateAttributes();
    }
    else{
        throw invalid_argument("New Charisma must be positive");
    }
}
// Recalculate attributes that depend on level or modifiers
void Character::recalculateAttributes(){
    hitPoints = calculateHitPoints();
    armorClass = calculateArmorClass();
    attackBonus = calculateAttackBonus();
    damageBonus = calculateDamageBonus();
}
//equip gear
void Character::equipArmor(string newArmor){
    armor = newArmor;
}
void Character::equipShield(string newShield){
    shield = newShield;
}
void Character::equipWeapon(string newWeapon){
    weapon = newWeapon;
}
void Character::equipBoots(string newBoots){
    boots = newBoots;
}
void Character::equipRing(string newRing){
    ring = newRing;
}
void Character::equipHelmet(string newHelmet){
    helmet = newHelmet;
}
// getters for Character stats
int Character::getLevel() const{return level;}
int Character::getHitPoints() const{return hitPoints;}
int Character::getArmorClass() const{return armorClass;}
int Character::getAttackBonus() const{return attackBonus;}
int Character::getDamageBonus() const{return damageBonus;}
// getters for abilities
int Character::getStrength() const{return strength;}
int Character::getDexterity() const{return dexterity;}
int Character::getConstitution() const{return constitution;}
int Character::getIntelligence() const{return intelligence;}
int Character::getWisdom() const{return wisdom;}
int Character::getCharisma() const{return charisma;}
// getters for abilitiy modifiers
int Character::getStrengthMod() const{return strengthMod;}
int Character::getDexterityMod() const{return dexterityMod;}
int Character::getConstitutionMod() const{return constitutionMod;}
int Character::getIntelligenceMod() const{return intelligenceMod;}
int Character::getWisdomMod() const{return wisdomMod;}
int Character::getCharismaMod() const{return charismaMod;}
// getters for equipment
string Character::getArmor() const{return armor;}
string Character::getShield() const{return shield;}
string Character::getWeapon() const{return weapon;}
string Character::getBoots() const{return boots;}
string Character::getRing() const{return ring;}
string Character::getHelmet() const{return helmet;}

void Character::printCharacter(){
    // Print attributes
    cout << "Level: " << getLevel() << "\n";
    cout << "Hit Points: " << getHitPoints() << "\n";
    cout << "Armor Class: " << getArmorClass() << "\n";
    cout << "Attack Bonus: " << getAttackBonus() << "\n";
    cout << "Damage Bonus: " << getDamageBonus() << "\n";
    // Print ability scores
    cout << "Ability Scores:" << "\n";
    cout << "  Strength: " << getStrength() << " (Mod: " << getStrengthMod() << ")" << "\n";
    cout << "  Dexterity: " << getDexterity() << " (Mod: " << getDexterityMod() << ")" << "\n";
    cout << "  Constitution: " << getConstitution() << " (Mod: " << getConstitutionMod() << ")" << "\n";
    cout << "  Intelligence: " << getIntelligence() << " (Mod: " << getIntelligenceMod() << ")" << "\n";
    cout << "  Wisdom: " << getWisdom() << " (Mod: " << getWisdomMod() << ")" << "\n";
    cout << "  Charisma: " << getCharisma() << " (Mod: " << getCharismaMod() << ")" << "\n";
    // Print equipment
    cout << "Equipment:" << "\n";
    cout << "  Armor: " << (getArmor().empty() ? "None" : getArmor()) << "\n";
    cout << "  Shield: " << (getShield().empty() ? "None" : getShield()) << "\n";
    cout << "  Weapon: " << (getWeapon().empty() ? "None" : getWeapon()) << "\n";
    cout << "  Boots: " << (getBoots().empty() ? "None" : getBoots()) << "\n";
    cout << "  Ring: " << (getRing().empty() ? "None" : getRing()) << "\n";
    cout << "  Helmet: " << (getHelmet().empty() ? "None" : getHelmet()) << "\n";
}
