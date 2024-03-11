#pragma once
class Observer{
    public:
        ~Observer();
        virtual void Update(string attribute, int newValue, int oldValue) = 0;
    protected:
        virtual Observer();
};
