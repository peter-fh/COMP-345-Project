#include "MySubject.h"
#include "MyObserver.h"

MySubject::MySubject(){
    _observers = new std::list<MyObserver*>;
}
MySubject::~MySubject(){
    delete _observers;
}
void MySubject::Attach(MyObserver* o){
    _observers->push_back(o);
}
void MySubject::Dettach(MyObserver* o){
    _observers->remove(o);
}
void MySubject::Notify() {
    for (auto i = _observers->begin(); i != _observers->end(); ++i){
        (*i)->Update();
    }
}
