rm driver.out
g++ -o driver.out -std=c++20 -Wno-c++11-extensions main.cpp Observer/Observer.cpp Dice/Dice.cpp Item/Item.cpp Item/Key.cpp Item/Chest.cpp Item/Weapon.cpp Item/Consumable.cpp Item/Armor.cpp Item/Loot.cpp Map/Mappable.cpp Character/Character.cpp Enemy/Enemy.cpp Enemy/Corpse.cpp Character/CharUI.cpp Map/Map.cpp Map/Campaign.cpp Map/MapEditor.cpp Map/MapEditorCLI.cpp Game/Game.cpp Enemy/Combat.cpp
./driver.out
