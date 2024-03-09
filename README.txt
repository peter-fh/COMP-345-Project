Eric Liu (40260654)
Jackson Abbott (40252068)
Peter Howe (40237623)
Wassim Bouchelouh

Date: February 25, 2024
Class: Comp 345

Assignment 1 README
This zip file contains 13 files including:
README.txt

Character.h (header file for Character)
Character.cpp (cpp file for Character)
CharacterTests.cpp (cpp file for unit tests for Character)
CharacterTests.exe (running unit tests for Character class functions)

Dice.h (header file for Dice)
Dice.cpp (cpp file for Dice)
(The dice function has a main program that prompts the user for an input of the amount of dices, 
type of dice and modifier. It then rolls the dice based on this function, outputting the sum of the rolls. 
It also includes the dice class which provides constructors that allow for dice objects with a specified amount of faces, 
the function checks if the amount of faces are valid and if not returns a 0 faces die. 
These dices have an overloaded roll function, where a default roll will give you a random number in your dice range, 
you can also specify an amount of rolls and a different dice type.)

map.h (header file for Map)
Map.cpp (cpp file for Map)
Map.exe

Item.cpp (cpp file for Item)

main.cpp (main function, where all the classes are be initialized)
driver.exe (running the main function)

Compilation command used is: 
g++ -o test main.cpp Character/Character.cpp Item/Item.cpp Observer/Observer.cpp Subject/Subject.cpp Dice/Dice.cpp Map/Map.cpp
