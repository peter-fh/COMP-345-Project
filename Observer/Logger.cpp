#include <iostream>
#include <chrono>
#include <ctime>
#include "Logger.h"


Logger::Logger(){
    sources = Sources();
    map = nullptr;
    character = nullptr;
    dice = nullptr;
    logFile = "log.txt";
}


Logger::Logger(std::string file_name){
    sources = Sources();
    map = nullptr;
    character = nullptr;
    dice = nullptr;
    logFile = file_name;
}


Logger::~Logger(){
    if (map != nullptr){
	map->Detach(this);
    }

    if (character != nullptr){
	character->Detach(this);
    }

    if (dice != nullptr){
	dice->Detach(this);
    }

}

void Logger::attachMap(Map* new_map){
    map = new_map;
}

void Logger::attachCharacter(Character* new_character){
    character = new_character;
}

void Logger::attachDice(Dice* new_dice){
    dice = new_dice;
}


void Logger::Update(Subject* subject){
    if (subject == map){
	logMap();
	return;
    }

    if (subject == character){
	logCharacter();
	return;
    }

    if (subject == dice){
	logDice();
	return;
    }
}


void Logger::logMap(){
    ofstream log;
    log.open(logFile.c_str(), std::ios_base::app);
    log << map->toString();
    log.flush();
    log.close();
}

void Logger::logCharacter(){
    ofstream log;
    log.open(logFile.c_str(), std::ios_base::app);
    log << character->toString();
    log.flush();
    log.close();
}


void Logger::logDice(){
    ofstream log;
    log.open(logFile.c_str(), std::ios_base::app);
    log << dice->toString();
    log.flush();
    log.close();
}



