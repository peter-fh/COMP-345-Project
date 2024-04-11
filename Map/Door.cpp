#include "Door.h"





Door::Door(bool o, int c){
    open = o;
    code = c;
}
int Door::getCode(){
    
}

void Door::unlock(Character* c){
    if (open) return;
    int count = 0;
    for (Item* i : c->inventory){
        Key* K = dynamic_cast<Key*>(i);
            if (K) {
                if (K->getCode() == code){
                    c->Notify("Used Key to Unlock Door");
                    open = true;
                    //gets rid of key
                    c->inventory.erase(c->inventory.begin() + count);
                    return;
                }}

        count++;
    }
    c->Notify("Door is locked");
}

void Door::unlock(){
    open = true;
}
