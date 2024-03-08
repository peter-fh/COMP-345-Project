#pragma once
#include "Observer.h"
#include "Character.h"
class PlayerCharacter : public Observer{
    public:
        PlayerCharacter(Character* c);
        ~PlayerCharacter();
        void Update();
        void display();
    private:
        Character *_subject;
};