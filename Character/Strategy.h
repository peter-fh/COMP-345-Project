#pragma once
#include "../Map/map.h"
#include "Character.h"
#include <iostream>

using namespace std;

class Strategy {
    public:
        ~Strategy() = default;
        virtual Cell move(Character movingChar, Map currentMap) = 0;
        virtual void attack(Character atkingChar, Map currentMap, int dmg) = 0;
        virtual void freeAction() = 0;
        
    protected:
        Character* character;
};

class HumanPlayerStrategy : public Strategy {
    public:
        // default constructor
        HumanPlayerStrategy() {
            this->character = nullptr;
        };

        // parametized constructor
        HumanPlayerStrategy(Character *c) {
            this->character = c;
            character->setStrategy(this);
        }

        // copy constructor
        HumanPlayerStrategy(const HumanPlayerStrategy& cs) {
            this->character = cs.character;
            character->setStrategy(this);
        }
        // character getter
        Character *getCharacter() {
            return character;
        }
        // character setter
        void setCharacter(Character* c) {
            this->character = c;
        }
        string getStrategyName() const {
            return "HumanPlayerStrategy";
        }

        Cell move(Character movingChar, Map currentMap) override{
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

            return currentMap.getCell(x,y);
        }
        void attack(Character atkingChar, Map currentMap, int dmg) override{
            int x,y;
            cout<<"Which cell would you like to move your Player Character to?"<<endl;
            cout<<"Enter the x coordinate:"<<endl;
            cin>> x;
            cout<<"Enter the y coordinate:"<<endl;
            cin>> y;
            Character enemy = *currentMap.getCell(x,y).character;
            if(currentMap.getCell(x,y).character != nullptr){
                enemy.setHP(enemy.getHitPoints()-dmg-atkingChar.getStrengthMod());
                cout<<"Human Player Attacked"<<endl;
            }
            else{
                cout<<"Not a Valid Target"<<endl;
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
int sign(int num) {
    return (num > 0) - (num < 0);
}

class AggressorStrategy : public Strategy {
    public:
        // default constructor
        AggressorStrategy() {
            this->character = nullptr;
        };

        // parametized constructor
        AggressorStrategy(Character *c) {
            this->character = c;
            character->setStrategy(this);
        }

        // copy constructor
        AggressorStrategy(const AggressorStrategy& cs) {
            this->character = cs.character;
            character->setStrategy(this);
        }
        // character getter
        Character *getCharacter() {
            return character;
        }
        // character setter
        void setCharacter(Character* c) {
            this->character = c;
        }
        string getStrategyName() const {
            return "AggressorStrategy";
        }

        Cell move(Character movingChar, Map currentMap)override {
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
                return movingChar.getLocation();
            }
            else{
                stepX = currentCell.x-destinationX;
                stepY = currentCell.y-destinationY;

                destinationX = destinationX+sign(stepX);
                destinationY = destinationY+sign(stepY);

                currentMap.setCell(destinationX,destinationY,OCCUPIED,movingChar);
                movingChar.setLocation(currentMap.getCell(destinationX,destinationY));
                cout<<"Enemy has moved"<<endl;
                currentMap.setCell(currentCell.x,currentCell.y,EMPTY);
                return currentMap.getCell(x,y);
            }   
        }

        void attack(Character atkingChar, Map currentMap, int dmg)override{
            Cell currentCell = atkingChar.getLocation();
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
            Character enemy = *currentMap.getCell(x,y).character;
            if(currentMap.getCell(x,y).character != nullptr){
                enemy.setHP(enemy.getHitPoints()-dmg-atkingChar.getStrengthMod());
                cout<<"Human Player Attacked"<<endl;
            }
            else{
                cout<<"Not a Valid Target"<<endl;
            }
        }
        void freeAction() override{
            cout<<"Aggressor Has No Free Action"<<endl;
        }
};


class FriendlyStrategy : public Strategy {
    public:
        // default constructor
        FriendlyStrategy() {
            this->character = nullptr;
        };

        // parametized constructor
        FriendlyStrategy(Character *c) {
            this->character = c;
            character->setStrategy(this);
        }

        // copy constructor
        FriendlyStrategy(const FriendlyStrategy& cs) {
            this->character = cs.character;
            character->setStrategy(this);
        }
        // character getter
        Character *getCharacter() {
            return character;
        }
        // character setter
        void setCharacter(Character* c) {
            this->character = c;
        }

        string getStrategyName() const {
            return "FriendlyStrategy";
        }


        Cell move(Character movingChar, Map currentMap) override{
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
                return movingChar.getLocation();
            }
            else{
                stepX = currentCell.x-destinationX;
                stepY = currentCell.y-destinationY;

                destinationX = destinationX+sign(stepX);
                destinationY = destinationY+sign(stepY);

                currentMap.setCell(destinationX,destinationY,OCCUPIED,movingChar);
                movingChar.setLocation(currentMap.getCell(destinationX,destinationY));
                cout<<"Enemy has moved"<<endl;
                currentMap.setCell(currentCell.x,currentCell.y,EMPTY);
                return currentMap.getCell(x,y);
            }
        }
        void attack(Character movingChar, Map currentMap, int dmg) override{
            cout<<"Friendly Does not Attack"<<endl;

        }
        void freeAction() override{
            cout<<"Friendly Has No Free Action"<<endl;
        }

        

};