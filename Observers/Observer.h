#include <list>

class Subject;


class Observer {
public:
    virtual ~Observer();
    virtual void Update(Subject *subject)=0;
protected:
    Observer();
};


class Subject {
public:
    virtual ~Subject();
    virtual void Attatch(Observer* o);
    virtual void Detatch(Observer* o);
    virtual void Notify();
protected:
    Subject();
private:
    std::list<Observer*> _observers;
};

