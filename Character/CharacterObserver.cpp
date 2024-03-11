#include "../Observer/Observer.h"
#include <iostream>

class CharacterObserver : public Observer{
  public:
    void Update(string attribute, int oldValue, int newValue){
      cout << attribute << " Updated: " << oldValue << " --> " << newValue;
    }
