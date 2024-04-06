#pragma once
#include <iostream>
#include <vector>
#include "../Character/CharUI.h"
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"


const int EMPTY = 0;
const int WALL = 1;
const int OCCUPIED = 2;
const int START = 3;
const int END = 4;

struct Cell {
    int x;
    int y;
    int type;
    Character* character;
    char character_char;
    Enemy* enemy = nullptr;
    bool hasEnemy = false;
    
    Cell() {
	x = 0; 
	y = 0; 
	type = EMPTY; 
	character = nullptr;
	enemy = nullptr;
    }

    Cell(int inp_x, int inp_y) {
	x = inp_x; 
	y = inp_y; 
	type = EMPTY; 
	character = nullptr;
	enemy = nullptr;
    }

    Cell(int inp_x, int inp_y, int inp_type) {
	x = inp_x; 
	y = inp_y; 
	type = inp_type; 
	character = nullptr;
	enemy = nullptr;
    }

    Cell(int inp_x, int inp_y, int inp_type, Character* inp_character) {
	x = inp_x; 
	y = inp_y; 
	type = inp_type; 
	character = inp_character;
	character_char = inp_character->getName()[0];
	enemy = nullptr;
    }

    Cell(int inp_x, int inp_y, int inp_type, Enemy* inp_enemy) {
	x = inp_x;
	y = inp_y;
	type = OCCUPIED;
	character = nullptr;
	enemy = inp_enemy;
	cout << "about to seg fault?" << endl;
	cout << enemy->getX();
	hasEnemy = true;
    }


};


typedef struct Cell Cell;
