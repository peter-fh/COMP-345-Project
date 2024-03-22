#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Character;
class Strategy {
    public:
        ~Strategy() = default;
        virtual void move() = 0;
        virtual void attack() = 0;
        virtual void freeAction() = 0;
        string getStrategyName() const{
            return "Null Strategy";
        };
        
    protected:
        Character* character;
};

class HumanPlayerStrategy : public Strategy {
    public:
        string getStrategyName() const {
            return "HumanPlayerStrategy";
        }

        void move() override{
            int x,y;
            cout<<"Which cell would you like to move your Player Character to?"<<endl;
            cout<<"Enter the x coordinate:"<<endl;
            cin>> x;
            cout<<"Enter the y coordinate:"<<endl;
            cin>> y;            
            cout<<"your Human Player Character is now on cell ("<<x<<","<<y<<")"<<endl;
        }
        void attack() override{
            int x,y;
            cout<<"Which cell would you like to move your Player Character to?"<<endl;
            cout<<"Enter the x coordinate:"<<endl;
            cin>> x;
            cout<<"Enter the y coordinate:"<<endl;
            cin>> y;
            cout<<"Human Player Attacked Character on cell ("<<x<<","<<y<<")"<<endl;
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
        string getStrategyName() const {
            return "AggressorStrategy";
        }

        void move()override {
            // int x,y,destinationX,destinationY,stepX,stepY;
            // for(x=0;x<currentMap.getWidth();x++){
            //     for(y=0;y<currentMap.getHeight();y++){
            //         if(currentMap.getCell(x,y).character != nullptr){
            //             currentDist = pow((x-currentCell.x),2)+pow((y-currentCell.y),2);
            //             if(currentDist<distance){
            //                 distance = currentDist;
            //                 destinationX = x;
            //                 destinationY = y;
            //             }
            //         }
            //     }
            // }
            // if(distance == LARGE_NUM){
            //     cout<<"The enemy did not move, as there are no Players on the map"<<endl;
            //     return movingChar.getLocation();
            // }
            // else{
            //     stepX = currentCell.x-destinationX;
            //     stepY = currentCell.y-destinationY;

            //     destinationX = destinationX+sign(stepX);
            //     destinationY = destinationY+sign(stepY);

            //     currentMap.setCell(destinationX,destinationY,OCCUPIED,movingChar);
            //     movingChar.setLocation(currentMap.getCell(destinationX,destinationY));
            //     cout<<"Enemy has moved"<<endl;
            //     currentMap.setCell(currentCell.x,currentCell.y,EMPTY);
            //     return currentMap.getCell(x,y);
            // }
            cout<<"Aggressor is moving towards nearest Player Character"<<endl;

        }

        void attack()override{
            // Cell currentCell = atkingChar.getLocation();
            // const int LARGE_NUM = 2147483647;
            // float distance=LARGE_NUM, currentDist;
            // int x,y,destinationX,destinationY,stepX,stepY;
            // for(x=0;x<currentMap.getWidth();x++){
            //     for(y=0;y<currentMap.getHeight();y++){
            //         if(currentMap.getCell(x,y).character != nullptr){
            //             currentDist = pow((x-currentCell.x),2)+pow((y-currentCell.y),2);
            //             if(currentDist<distance){
            //                 distance = currentDist;
            //                 destinationX = x;
            //                 destinationY = y;
            //             }
            //         }
            //     }
            // }
            // Character enemy = *currentMap.getCell(x,y).character;
            // if(currentMap.getCell(x,y).character != nullptr){
            //     enemy.setHP(enemy.getHitPoints()-dmg-atkingChar.getStrengthMod());
            //     cout<<"Human Player Attacked"<<endl;
            // }
            // else{
            //     cout<<"Not a Valid Target"<<endl;
            // }
            cout<<"Aggressor is attacking the nearest Player Character"<<endl;

        }
        void freeAction() override{
            cout<<"Aggressor Has No Free Action"<<endl;
        }
};


class FriendlyStrategy : public Strategy {
    public:
        string getStrategyName() const {
            return "FriendlyStrategy";
        }


        void move() override{
            // Cell currentCell = movingChar.getLocation();
            // const int LARGE_NUM = 2147483647;
            // float distance=LARGE_NUM, currentDist;
            // int x,y,destinationX,destinationY,stepX,stepY;
            // for(x=0;x<currentMap.getWidth();x++){
            //     for(y=0;y<currentMap.getHeight();y++){
            //         if(currentMap.getCell(x,y).character != nullptr){
            //             currentDist = pow((x-currentCell.x),2)+pow((y-currentCell.y),2);
            //             if(currentDist<distance){
            //                 distance = currentDist;
            //                 destinationX = x;
            //                 destinationY = y;
            //             }
            //         }
            //     }
            // }
            // if(distance == LARGE_NUM){
            //     cout<<"The enemy did not move, as there are no Players on the map"<<endl;
            //     return movingChar.getLocation();
            // }
            // else{
            //     stepX = currentCell.x-destinationX;
            //     stepY = currentCell.y-destinationY;

            //     destinationX = destinationX+sign(stepX);
            //     destinationY = destinationY+sign(stepY);

            //     currentMap.setCell(destinationX,destinationY,OCCUPIED,movingChar);
            //     movingChar.setLocation(currentMap.getCell(destinationX,destinationY));
            //     cout<<"Enemy has moved"<<endl;
            //     currentMap.setCell(currentCell.x,currentCell.y,EMPTY);
            //     return currentMap.getCell(x,y);
            // }
            cout<<"Friend is moving towards the nearest Player Character"<<endl;


        }
        void attack() override{
            cout<<"Friendly Does not Attack"<<endl;

        }
        void freeAction() override{
            cout<<"Friendly Has No Free Action"<<endl;
        }
};
