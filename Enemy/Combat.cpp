#include "Combat.h"
#include "Corpse.h"
#include <chrono>
#include <thread>

void Combat::displayTexture(){
    for (int i=0; i < 20; i++){
	cout << "\n";
    }
    string texture[10] = {
	"             \\  O    ",
	"      O  /    \\/|\\   ",
	"     /|\\/      / \\   ",
	"     / \\             "
    };
    for (int i = 0; i < 4; i++){
	std::cout << texture[i] << "\n";
    }

    cout << "\n\n";
}
Combat::Combat(Character& player, Enemy& enemy){
    displayTexture();		    
    Dice d20 = Dice(20);
    std::string selection = "";
    int dmg;
    
    std::cout << "Amushed by " << enemy.name << " (Level " << enemy.level << ") " << enemy.maxHP << "HP\n";
    enemy.equipment();

    std::this_thread::sleep_for(2s); 
    while (player.alive && enemy.alive){

	displayTexture();		    
        selection = "";
        std::cout << "\n" << player.status();
        std::cout << "\nPlayer Move: \n\t1: Attack\n\t2: Attack with bow\n\t3: Flee\n";
	std::cout << "#: ";
        std::getline(cin, selection);
        if (selection != "1" && selection != "2" && selection != "3"){ 
            do{
                std::cout << "\nInvalid, please try again";
                std::cout << "Player Move: \n   1: Attack\n   2: Attempt to Flee\n";
                std::getline(cin, selection);
            } while (selection != "1" && selection != "2" && selection != "3");
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
		float dmg = player.attack(static_cast<float>(roll) / 20.0f);	
                enemy.takeDamage(dmg);
                if (enemy.alive == false){
                    return;
                }
            }
        if (selection == "2"){
                int roll = d20.Roll();
                std::cout << "\nRolling D20";
                std::this_thread::sleep_for(0.2s); 
                std::cout << "\nRolled: " << roll << "\n";
                if (roll == 20){
                    cout << "\n!CRIT!";
                }
		        float dmg = player.attack(static_cast<float>(roll) / 20.0f);	
                enemy.takeDamage(dmg);
                if (enemy.alive == false){
                    return;
                }
            }
        if (selection == "3"){
            int roll = d20.Roll();
            if (roll < 15){
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
    if (!enemy.alive){
        player.gainXP(enemy.level);
	    enemy.kill();
        std::this_thread::sleep_for(2s); 
        }        
    if (!player.alive){
	exit(0);
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
