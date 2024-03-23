rm log.txt
g++ -o driver.out -Wno-c++11-extensions main.cpp Observer/Observer.cpp Item/Item.cpp Dice/Dice.cpp Character/Character.cpp Character/CharacterObserver.cpp Character/PlayerCharacter.cpp Character/CharUI.cpp Map/Map.cpp Map/Campaign.cpp Map/MapEditor.cpp Map/MapEditorCLI.cpp Observer/Logger.cpp
./driver.out
