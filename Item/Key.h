#include "Item.h"
#include "../Map/Mappable.h"


class Key : public Item {
    bool key = true;
    public:
        Key(int code);
        int getCode();
        char getSymbol() override;
    private:
        int code;
};