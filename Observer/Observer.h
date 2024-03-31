#pragma once
#include <cmath>
#include <string>
#include <list>

class Subject;

class Observer{
public:
    virtual ~Observer();
    Observer();
    virtual void Update(Subject* subject) = 0;      
    virtual void Update(std::string attribute, int newValue, int oldValue);
	virtual void Update(std::string message);
	    virtual void Update() {}
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
