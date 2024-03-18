#pragma once
#include "MyObserver.h"
#include <list>
using namespace std;

class MySubject{
    public:
        virtual void Attach(MyObserver* o)=0;
        virtual void Dettach(MyObserver* o)=0;
        virtual void Notify()=0;
        MySubject();
        ~MySubject();
    private:
        list<MyObserver*>*_observers;
};
