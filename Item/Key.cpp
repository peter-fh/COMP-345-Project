#include "Key.h"

Key::Key(int c){
    const int code = c;
}

int Key::getCode(){
    return code;
}
char Key::getSymbol(){
    return 'K';
    //special
}