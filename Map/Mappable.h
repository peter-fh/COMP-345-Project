#ifndef MAPPABLE_H
#define MAPPABLE_H


class Mappable{
private:
    int xCoord, yCoord;
    bool active;
    char symbol;

public:
    void setX(int newX);
    void setY(int newY);
    int getX();
    int getY();
    void activate();
    void deactivate();
    bool isActive();

    
    char getSymbol();
    void setSymbol(char newSymbol);
    virtual void determineSymbol() = 0;


};

#endif // MAPPABLE_H
