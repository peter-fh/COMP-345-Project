#pragma once
class MyObserver{
    public:
        ~MyObserver();
        virtual void Update() = 0;
    protected:
        MyObserver();
};