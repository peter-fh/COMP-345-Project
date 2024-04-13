#include "../Map/MapEditorCLI.h"
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Item/Loot.h"
#include "../Item/Armor.h"
#include "../Item/Weapon.h"
#include "../Item/Bow.h"
#include "../Dice/Dice.h"
#include <iostream>
#include <vector>

class StartingUI{
    static void MapBuilder();
    static void CharacterBuilder();
    static void NPCBuilder();
};
