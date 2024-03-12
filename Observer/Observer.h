#pragma once
class Observer{
    public:
        ~Observer();
        virtual void Update(string attribute, int newValue, int oldValue) = 0;    
        virtual void Update(string attribute, int newValue) = 0;
        virtual void Update(string attribute) = 0;  
        virtual void Update() = 0;  
    protected:
        virtual Observer();
};
