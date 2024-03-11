#pragma once
class Observer{
    public:
        ~Observer();
        virtual void Update(string attribute, int newValue) = 0;
    protected:
        virtual Observer();
};
