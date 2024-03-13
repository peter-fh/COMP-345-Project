#include "../Observer/Observer.h"
#include <iostream>

class CharacterObserver : public Observer{
  public:
    void Update(std::string attribute, int oldValue, int newValue){
    std::cout << attribute << " Updated: " << oldValue << " --> " << newValue;
    }
};
