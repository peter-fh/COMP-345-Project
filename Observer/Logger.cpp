#include <cassert>
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
    logMap();
}

void Logger::attachCharacter(Character* new_character){
    character = new_character;
    logCharacter();
}

void Logger::attachDice(Dice* new_dice){
    dice = new_dice;
    logDice();
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


void Logger::Update(){}


void Logger::logMap(){
    ofstream log;
    log.open(logFile.c_str(), std::ios_base::app);

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    char* now_str = std::ctime(&now_c);

    log << "Map changed at " << now_str << "\n";
    log << map->toString();
    log << "\n";
    log.flush();
    log.close();
}

void Logger::logCharacter(){
    ofstream log;
    log.open(logFile.c_str(), std::ios_base::app);
 
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    char* now_str = std::ctime(&now_c);

    log << "Character changed at " << now_str << "\n";   
    log << character->toString();
    log << "\n";
    log.flush();
    log.close();
}


void Logger::logDice(){
    ofstream log;
    log.open(logFile.c_str(), std::ios_base::app);
 
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    char* now_str = std::ctime(&now_c);

    log << "Dice changed at " << now_str << "\n";   
    log << dice->toString();
    log << "\n";
    log.flush();
    log.close();
}



