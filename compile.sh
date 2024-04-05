g++ -o driver.out -std=c++20 -Wno-c++11-extensions main.cpp Observer/Observer.cpp Item/Items.cpp Dice/Dice.cpp Character/Item.cpp Character/Weapon.cpp Character/Consumable.cpp Character/Armor.cpp Character/Corpse.cpp Character/Character.cpp Character/CharacterObserver.cpp Character/PlayerCharacter.cpp Character/CharUI.cpp Character/CharacterBuilder.cpp Map/Map.cpp Map/Campaign.cpp Map/MapEditor.cpp Map/MapEditorCLI.cpp Game/Game.cpp 
./driver.out
rm driver.out
