#pragma once
#include "../Map/map.h"
#include "Character.h"
#include <iostream>

using namespace std;

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void move(Character movingChar, Map currentMap) = 0;
    virtual void attack(Cell toAttack, int dmg) = 0;
    virtual void freeAction() = 0;
};

class HumanPlayerStrategy : public Strategy {
    public:
        void move(Character movingChar, Map currentMap) override{
            Cell currentCell = movingChar.getLocation();
            int x,y;
            cout<<"Which cell would you like to move your Player Character to?"<<endl;
            cout<<"Enter the x coordinate:"<<endl;
            cin>> x;
            cout<<"Enter the y coordinate:"<<endl;
            cin>> y;            
            currentMap.setCell(x,y,OCCUPIED,movingChar);
            movingChar.setLocation(currentMap.getCell(x,y));
            cout<<"your character is now on cell ("<<x<<","<<y<<")"<<endl;
            currentMap.setCell(currentCell.x,currentCell.y,EMPTY);
        }
        void attack(Cell toAttack, int dmg) override{
            Character enemy = *toAttack.character;
            if(toAttack.character != nullptr){
                enemy.setHP(enemy.getHitPoints()-dmg);
                cout<<"Human Player Attacked";
            }
            else{
                cout<<"Not a Valid Target";
            }
            
        }
        void freeAction() override{
            const char* options[4]= { "Drop an object", "Speak a few words", "erform a Gesture", "Other small tasks" };
            int choice;
            cout<<"Human Player Free Action"<<endl;
            cout<<"What would you like to do?"<<endl;
            cout<<"[1] Drop an object\n[2] Speak a few words\n[3] Perform a Gesture\n[4] Do other small tasks."<<endl;
            cout<<"Enter your choice (integer)"<<endl;
            cin>>choice;
            cout<<"Human player decided to "<<options[choice]<<endl;
        }
};

class AggressorStrategy : public Strategy {
    public:
        void move(Character movingChar, Map currentMap) override{
            Cell currentCell = movingChar.getLocation();
            const int LARGE_NUM = 2147483647;
            float distance=LARGE_NUM, currentDist;
            int x,y,destinationX,destinationY,stepX,stepY;
            for(x=0;x<currentMap.getWidth();x++){
                for(y=0;y<currentMap.getHeight();y++){
                    if(currentMap.getCell(x,y).character != nullptr){
                        currentDist = pow((x-currentCell.x),2)+pow((y-currentCell.y),2);
                        if(currentDist<distance){
                            distance = currentDist;
                            destinationX = x;
                            destinationY = y;
                        }
                    }
                }
            }
            if(distance == LARGE_NUM){
                cout<<"The enemy did not move, as there are no Players on the map"<<endl;
            }
            else{
                stepX = currentCell.x-destinationX;
                stepY = currentCell.y-destinationY;
                destinationX = destinationX+signbit(stepX);
                destinationY = destinationY+signbit(stepY);

                currentMap.setCell(destinationX,destinationY,OCCUPIED,movingChar);
                movingChar.setLocation(currentMap.getCell(destinationX,destinationY));

                currentMap.setCell(currentCell.x,currentCell.y,EMPTY);
                cout<<"Enemy has moved Player Move";
            }
            


            
        }
        void attack(Cell toAttack, int dmg) override{
            Character enemy = *toAttack.character;
            if(toAttack.character != nullptr){
                enemy.setHP(enemy.getHitPoints()-dmg);
            }

        }
        void freeAction() override{
            cout<<"Aggressor Has No Free Action";
        }
};

class FriendlyStrategy : public Strategy {
    public:
        void move(Character movingChar, Map currentMap) override{

        }
        void attack(Cell toAttack, int dmg) override{

        }
        void freeAction() override{
            cout<<"Friendly Has No Free Action";
        }
};