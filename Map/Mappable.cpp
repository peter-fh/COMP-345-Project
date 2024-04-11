#include "Mappable.h"

void Mappable::setX(int newX){
    xCoord = newX;
}
void Mappable::setY(int newY){
    yCoord = newY;
}

int Mappable::getX(){return xCoord;}
int Mappable::getY(){return yCoord;}

void Mappable::activate(){active = true;}
void Mappable::deactivate(){active = false;}
bool Mappable::isActive(){return active;}

char Mappable::getSymbol(){return symbol;}
void Mappable::setSymbol(char newSymbol){symbol = newSymbol;}
void Mappable::determineSymbol(){setSymbol(' ');}
