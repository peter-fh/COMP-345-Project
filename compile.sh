rm log.txt
g++ -o driver.out -Wno-c++11-extensions main.cpp Observer/Observer.cpp Item/Items.cpp Dice/Dice.cpp Item/Item.cpp Item/Weapon.cpp Item/Consumable.cpp Item/Armor.cpp Item/Loot.cpp Enemy/Enemy.cpp Enemy/Corpse.cpp Character/Character.cpp Character/CharacterObserver.cpp Character/PlayerCharacter.cpp Character/CharUI.cpp Character/CharacterBuilder.cpp Map/Map.cpp Enemy/Combat.cpp Map/Campaign.cpp Map/MapEditor.cpp Map/MapEditorCLI.cpp Observer/Logger.cpp
./driver.out
rm driver.out
