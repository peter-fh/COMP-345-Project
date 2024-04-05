g++ -o driver.out -std=c++20 -Wno-c++11-extensions main.cpp Observer/Observer.cpp Item/Items.cpp Dice/Dice.cpp Item/Item.cpp Item/Weapon.cpp Item/Consumable.cpp Item/Armor.cpp Item/Loot.cpp Character/Character.cpp Enemy/Enemy.cpp Enemy/Corpse.cpp Character/CharUI.cpp Character/CharacterBuilder.cpp Map/Map.cpp Map/Campaign.cpp Map/MapEditor.cpp Map/MapEditorCLI.cpp Game/Game.cpp Enemy/Combat.cpp
./driver.out
rm driver.out
