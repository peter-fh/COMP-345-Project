#include "Mappable.h"
#include "map.h"
#include "../Item/Key.h"
#include "../Character/Character.h"

class Door : public Mappable{
    public:
        void unlock(Character* player);
        void unlock();
        bool open;
        Door(bool open, int code);
        char getSymbol();
        int getCode();
    private:
        int code;
};