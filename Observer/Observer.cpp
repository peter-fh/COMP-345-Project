#include "Observer.h"

Observer::~Observer(){}

Observer::Observer(){}

Subject::Subject(){
    _observers = new list<Observer*>;
}
Subject::~Subject(){
    delete _observers;
}

void Subject::Detach(Observer* o){
    _observers->remove(o);
}
void Subject::Attach(Observer* o){
    list<Observer *>::iterator i = _observers->begin();
}

void Subject::Notify(){}
