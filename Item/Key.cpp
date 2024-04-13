#include "Key.h"

Key::Key(int c){
    const int code = c;
    itemName = "Key";
}

int Key::getCode(){
    return code;
}

void Key::determineSymbol(){
    setSymbol('K');
}
