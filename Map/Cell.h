#pragma once
#include <iostream>
#include <vector>
#include "../Character/CharUI.h"
#include "../Character/Character.h"



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
    bool has_enemy;
    
    Cell() {
	x = 0; 
	y = 0; 
	type = EMPTY; 
	character = nullptr;
	has_enemy = false;
    }

    Cell(int inp_x, int inp_y) {
	x = inp_x; 
	y = inp_y; 
	type = EMPTY; 
	character = nullptr;
	has_enemy = false;
    }

    Cell(int inp_x, int inp_y, int inp_type) {
	x = inp_x; 
	y = inp_y; 
	type = inp_type; 
	character = nullptr;
	has_enemy = false;
    }

    Cell(int inp_x, int inp_y, int inp_type, Character* inp_character) {
	x = inp_x; 
	y = inp_y; 
	type = inp_type; 
	character = inp_character;
	character_char = inp_character->getName()[0];
	has_enemy = false;
    }

    Cell(int inp_x, int inp_y, bool has_enemy) {
	x = inp_x;
	y = inp_y;
	type = OCCUPIED;
	has_enemy = true;
	character = nullptr;
	character_char = 'E';
    }


};


typedef struct Cell Cell;
