#pragma once
#include <string>
#include <list>


class Observer{
    public:
        virtual ~Observer();
        Observer();
        virtual void Update(std::string attribute, int newValue, int oldValue) = 0;      
};

using namespace std;
class Subject{
    public:
        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
	virtual void Notify();
        Subject();
        ~Subject();
	
    private:
        list<Observer*> *_observers;
};
