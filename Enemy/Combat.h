#pragma once
#include "Enemy.h"
#include "../Character/Character.h"
#include <iostream>
#include <string>

class Combat{
    public:
        Combat(Character& inp_player, Enemy& inp_enemy);
};
