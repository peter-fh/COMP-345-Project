#include "Combat.h"
#include <chrono>
#include <thread>

Combat::Combat(Character& player, Enemy& enemy){
    enemy.alive = false;
    return;
    Dice d20 = Dice(20);
    std::string selection;
    int dmg;
    
    std::cout << "Amushed by " << enemy.name << " (Level " << enemy.level << ") " << enemy.maxHP << "HP\n";
    enemy.equipment();

    std::this_thread::sleep_for(2s); 
    std::cout << "Player is alive: " << player.alive << "\n";
    std::cout << "Enemy is alive: " << enemy.alive << "\n";
    while (player.alive && enemy.alive){
        selection = "";
        std::cout << "\n" << player.status();
        std::cout << "\nPlayer Move: \n   1: Attack\n   2: Attempt to Flee\n";
        std::getline(cin, selection);
        if (selection != "1" && selection != "2"){ 
            do{
                std::cout << "\nInvalid, please try again";
                std::cout << "Player Move: \n   1: Attack\n   2: Attempt to Flee\n";
                std::getline(cin, selection);
            } while (selection != "1" && selection != "2");
                  }
        std::this_thread::sleep_for(0.5s); 
        //make it look better
        if (selection == "1"){
                int roll = d20.Roll();
                std::cout << "\nRolling D20";
                std::this_thread::sleep_for(0.2s); 
                std::cout << "\nRolled: " << roll << "\n";
                if (roll == 20){
                    cout << "\n!CRIT!";
                }
		cout << "before player attack\n";
		float dmg = player.attack(static_cast<float>(roll) / 20.0f);	
		cout << "before enemy take damage\n";
                enemy.takeDamage(dmg);
		cout << "after enemy take damage\n";
                if (enemy.alive == false){
                    return;
                }
            }
        if (selection == "2"){
            int roll = d20.Roll();
            if (roll < 10){
                cout << "\nSuccessfully Fled";
                enemy.playerFlee();
                return;
            }
            else{
                cout << "\nCan't escape";
            }
        }

        std::cout << "\n" << enemy.status();
        std::this_thread::sleep_for(2s); 


        std::cout << "\n" << enemy.name << "'s Move" << "\n\n" << enemy.name << " Attacks";
        std::this_thread::sleep_for(0.2s); 
        int roll = d20.Roll();
        std::cout << "\nRolling D20";
        std::this_thread::sleep_for(0.2s); 
        std::cout << "\nRolled: " << roll;
        if (roll == 20){
            cout << "\n!CRIT!";
        }
        dmg = enemy.Attack(static_cast<float>(roll) / 20.0f);
        player.takeDamage(dmg);
        
        std::this_thread::sleep_for(2s); 

        }
    /* if (enemy->alive == false){
	//PLACE CORPSE ON MAP HERE NEXT VERSION  
	selection = "";
	Corpse c = enemy->kill();
	std::cout << "\nSearch?\n   1: Yes\n    2: No";
	std::getline(cin, selection);
	if (selection != "1" && selection != "2"){ 
	    do{
		std::cout << "\nInvalid, please try again";
		std::cout << "\nSearch?\n   1: Yes\n    2: No\n";;
		std::getline(cin, selection);
	    } while (selection != "1" && selection != "2");
	}
	if (selection == "1"){
	    c.search();
	}   
    } */
        
}
