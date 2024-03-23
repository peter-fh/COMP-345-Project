#ifndef CHARACTER_BUILDER_H
#define CHARACTER_BUILDER_H

#include "Character.h"
#include "Character.cpp"
#include <iostream>

using namespace std;

// Builder Interface
class CharacterBuilder
{
public:
    virtual void buildAbilityScores() = 0;
    virtual Character *getCharacter() = 0;
    virtual ~CharacterBuilder() {}

    static int generateAbilityScore()
    {
        int n = 4;
        int roll[4];
        for (int i = 0; i < n; i++)
        { // rolling 4d6
            roll[i] = std::rand() % (6 - 1) + 1;
        }
        std::sort(roll, roll + n);
        return roll[1] + roll[2] + roll[3];
    }
};

class BullyCharacterBuilder : public CharacterBuilder
{
private:
    Character *character;

public:
    BullyCharacterBuilder(int level)
    {
        character = new Character(level);
    }

    void buildAbilityScores() override
    {
        character->setStrength(generateAbilityScore());
        character->setConstitution(generateAbilityScore());
        character->setDexterity(generateAbilityScore());
        character->setIntelligence(generateAbilityScore());
        character->setCharisma(generateAbilityScore());
        character->setWisdom(generateAbilityScore());
    }

    Character *getCharacter() override
    {
        return character;
    }
};

class NimbleCharacterBuilder : public CharacterBuilder
{
private:
    Character *character;

public:
    NimbleCharacterBuilder(int level)
    {
        character = new Character(level);
    }

    void buildAbilityScores() override
    {
        character->setDexterity(generateAbilityScore());
        character->setConstitution(generateAbilityScore());
        character->setStrength(generateAbilityScore());
        character->setIntelligence(generateAbilityScore());
        character->setCharisma(generateAbilityScore());
        character->setWisdom(generateAbilityScore());
    }

    Character *getCharacter() override
    {
        return character;
    }
};

class TankCharacterBuilder : public CharacterBuilder
{
private:
    Character *character;

public:
    TankCharacterBuilder(int level)
    {
        character = new Character(level);
    }

    void buildAbilityScores() override
    {
        // Generate ability scores randomly
        // Assign ability scores for a Tank fighter
        // For example:
        character->setConstitution(generateAbilityScore());
        character->setDexterity(generateAbilityScore());
        character->setStrength(generateAbilityScore());
        character->setIntelligence(generateAbilityScore());
        character->setCharisma(generateAbilityScore());
        character->setWisdom(generateAbilityScore());
    }

    Character *getCharacter() override
    {
        return character;
    }
};

int main()
{
    // Create a Bully fighter
    CharacterBuilder *bullyBuilder = new BullyCharacterBuilder(1);
    bullyBuilder->buildAbilityScores();
    Character *bully = bullyBuilder->getCharacter();

    // Create a Nimble fighter
    CharacterBuilder *nimbleBuilder = new NimbleCharacterBuilder(1);
    nimbleBuilder->buildAbilityScores();
    Character *nimble = nimbleBuilder->getCharacter();

    // Create a Tank fighter
    CharacterBuilder *tankBuilder = new TankCharacterBuilder(1);
    tankBuilder->buildAbilityScores();
    Character *tank = tankBuilder->getCharacter();

    // Print details of each character
    std::cout << "Bully Fighter:\n";
    bully->printCharacter();
    std::cout << "\n\n";

    std::cout << "Nimble Fighter:\n";
    nimble->printCharacter();
    std::cout << "\n\n";

    std::cout << "Tank Fighter:\n";
    tank->printCharacter();
    std::cout << "\n\n";

    // Clean up memory
    delete bullyBuilder;
    delete bully;
    delete nimbleBuilder;
    delete nimble;
    delete tankBuilder;
    delete tank;

    return 0;
}

#endif // CHARACTER_BUILDER_H
