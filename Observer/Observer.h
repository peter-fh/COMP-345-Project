#pragma once
#include <string>


class Observer{
    public:
        virtual ~Observer();
        Observer();
        virtual void Update(std::string attribute, int newValue, int oldValue) = 0;      
};
