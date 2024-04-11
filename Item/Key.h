#include "Item.h"
#include "../Map/Mappable.h"


class Key : public Item {
    bool key = true;
    public:
        Key(int code);
        int getCode();
    private:
        int code;
};