#include "PlayerCharacter.h"
#include "Character.h"
#include <iostream>
using namespace std;
PlayerCharacter::PlayerCharacter(Character* c){
    _subject = c;
    _subject->Attach(this);
};
PlayerCharacter::~PlayerCharacter(){
    _subject->Detach(this);
};
void PlayerCharacter::Update(){
    display();
}
void PlayerCharacter::display(){
    
}