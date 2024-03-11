#include "../Observer/Observer.h"
#include <iostream>

class CharacterObserver : public Observer{
  public:
    void Update(string attribute, int NewValue, int oldValue){
      cout << attribute << " Updated: " << oldValue << " --> " << newValue;
    }
