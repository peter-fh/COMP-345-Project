#pragma once
#include "../Observer/Observer.h"
#include "../Character/Character.h"
class PlayerCharacter : public Observer{
    public:
        PlayerCharacter(Character* c);
        ~PlayerCharacter();
        void Update();
        void display();
    private:
        Character *_subject;
};
