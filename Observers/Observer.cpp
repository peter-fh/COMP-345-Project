#include "Observer.h"

void Subject::Attatch(Observer *o){
    _observers.push_back(o);
}

void Subject::Detatch(Observer *o){
    _observers.remove(o);
}


void Subject::Notify(){
    std::list<Observer*>::iterator it = _observers.begin();
    for (; it != _observers.end();++it){ 
        (*it)->Update(this);
    }
}
