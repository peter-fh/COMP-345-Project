#pragma once
#include "MyObserver.h"
#include <list>
using namespace std;

class MySubject{
    public:
        virtual void Attach(MyObserver* o);
        virtual void Dettach(MyObserver* o);
        virtual void Notify();
        MySubject();
        ~MySubject();
    private:
        list<MyObserver*>*_observers;
};