#include "Enemy.h"
#include "../Character/Character.h"
#include <iostream>
#include <string>

class Combat{
    public:
        Character* player;
        Enemy* enemy;
        Combat(Character*, Enemy*);
};
