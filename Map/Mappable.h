#ifndef MAPPABLE_H
#define MAPPABLE_H

class Mappable{
    int xCoord, yCoord;
    
    void setX(int newX);
    void setY(int newY);
    virtual char getSymbol();

    int getX();
    int getY();



};

#endif // MAPPABLE_H