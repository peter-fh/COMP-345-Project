#include <stdio.h>
#include "Logger.h"


Logger::Logger(){
    Logger("log.txt");
}


Logger::Logger(std::string file_name){
    sources = Sources();
    map = nullptr;
    character = nullptr;
    dice = nullptr;
    std::string log_file_name = "../" + file_name;
    logFile.open(log_file_name.c_str());
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
    logFile << map->toString();
}

void Logger::logCharacter(){
    logFile << character->toString();
}


void Logger::logDice(){
    logFile << dice->toString();
}


