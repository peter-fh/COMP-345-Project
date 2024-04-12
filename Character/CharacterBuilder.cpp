#ifndef CHARACTER_BUILDER_H
#define CHARACTER_BUILDER_H

#include "Character.h"
#include <iostream>

using namespace std;

// Builder Interface
class CharacterBuilder
{
public:
    virtual void buildAbilityScores() = 0;
    virtual Character *getCharacter() = 0;
    ~CharacterBuilder() {}

    static int generateAbilityScore()
    {
        int n = 4;
        int roll[4];
        for (int i = 0; i < n; i++)
        { // rolling 4d6
            roll[i] = std::rand() % (6 - 1) + 1;
        }
        //std::sort(roll, roll + n);
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

    }

    Character *getCharacter() override
    {
        return character;
    }
};
#endif // CHARACTER_BUILDER_H
