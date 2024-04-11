#include "Item.h"
#include "../Map/Mappable.h"


class Key : public Item, public Mappable{
    bool key = true;
    public:
        Key(int code);
        int getCode();
	void determineSymbol() override;
    private:
        int code;
};
