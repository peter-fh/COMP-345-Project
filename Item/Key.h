#include "Item.h"
#include "../Map/Mappable.h"

class Key : public Item, public Mappable
{
public:
    Key(int code);
    Key();
    int getCode();
    void determineSymbol() override;

    void serialize(std::ostream &out) const override;
    void deserialize(std::istream &in) override;

private:
    int code;
    bool key = true;
};
