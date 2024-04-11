#pragma once
#include <iostream>
#include <vector>
#include "Mappable.h"


const int EMPTY = 0;
const int WALL = 1;
const int OCCUPIED = 2;
const int START = 3;
const int END = 4;

struct Cell {
    int x;
    int y;
    int type;
    Mappable* mappable_obj;
    
    Cell() {
	x = 0; 
	y = 0; 
	type = EMPTY; 
	mappable_obj = nullptr;
    }

    Cell(int inp_x, int inp_y) {
	x = inp_x; 
	y = inp_y; 
	type = EMPTY; 
	mappable_obj = nullptr;
    }

    Cell(int inp_x, int inp_y, int inp_type) {
	if (inp_type == OCCUPIED) {
	    std::cerr << "Error: Must provide a character for an OCCUPIED cell\n";
	}
	x = inp_x; 
	y = inp_y; 
	type = inp_type; 
	mappable_obj = nullptr;
    }

    Cell(int inp_x, int inp_y, int inp_type, Mappable* inp_mappable_obj) {
	if (inp_type != OCCUPIED) {
	    std::cerr << "Error: Incorrect constructor used for non-occupied cell\n";
	}
	x = inp_x; 
	y = inp_y; 
	type = inp_type; 
	mappable_obj = inp_mappable_obj;

    }


};


typedef struct Cell Cell;
