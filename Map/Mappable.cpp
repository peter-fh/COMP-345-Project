#include "Mappable.h"

void Mappable::setX(int newX){
    xCoord = newX;
}
void Mappable::setY(int newY){
    yCoord = newY;
}

int Mappable::getX(){return xCoord;}
int Mappable::getY(){return yCoord;}