#include "Observer.h"
#include <iostream>

Observer::~Observer(){}

Observer::Observer(){}

void Observer::Update(string attribute, int newValue, int oldValue){}
void Observer::Update(string message){}
void Observer::Update() {}

Subject::Subject(){
    _observers = new list<Observer*>;
}
Subject::~Subject(){
    list<Observer *>::iterator it = _observers->begin();
    for (;it != _observers->end(); it++){
	delete *it;
    } 

    // WARNING: caused seg fault in Map
    // delete _observers;
}

void Subject::Detach(Observer* o){
    _observers->remove(o);
}
void Subject::Attach(Observer* o){
    _observers->push_back(o);
}


void Subject::Notify(){

    list<Observer *>::iterator i = _observers->begin();
    for (;i != _observers->end();i++){
        (*i)->Update(this);
    }
}
