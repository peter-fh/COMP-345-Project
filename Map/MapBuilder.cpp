#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MapEditor.h"

// Abstract builder interface
class MapBuilder
{
public:
    virtual bool loadMap(const std::string &filename) = 0;
    virtual Map *getMap() = 0;
};

// Concrete builder for reading the map as saved
class MapSavedBuilder : public MapBuilder
{
private:
    Map *map;

public:
    MapSavedBuilder() : map(nullptr) {}

    bool loadMap(const std::string &filename) override
    {
        ifstream inputFile("../mapInfo.txt");
	bool returnBool = true;

        // Check if the file is opened successfully
        if (!inputFile.is_open())
        {
            cerr << "Error opening the file." << endl;
	    returnBool = false;
	    
        }


        // Read attributes from the file
        string mapName;
        int width;
        int height;
        inputFile >> mapName >> width >> height;
	cout << mapName;

        // Close the file
        inputFile.close();
	


        map = (new Map(width, height, mapName));

	return returnBool;

        // Implement code to read map data from file and construct the map
        // Example:
        // ifstream file(filename);
        // Read map data...
        // Construct map object...
    }

    Map *getMap() override
    {
        return map;
    }
};

// Concrete builder for adapting the map to a specific level during gameplay
class MapGamePlayBuilder : public MapBuilder
{
private:
    Map *map;

public:
    MapGamePlayBuilder() : map(nullptr) {}

    bool loadMap(const std::string &filename) override
    {

        ifstream inputFile("mapInfo.txt");

	bool returnBool = true;

        // Check if the file is opened successfully
        if (!inputFile.is_open())
        {
            cerr << "Error opening the file." << endl;
	    returnBool = false; 
        }

        // Read attributes from the file
        string mapName;
        int level;
        int width;
        int height;
        inputFile >> mapName >> level >> width >> height;

        // Close the file
        inputFile.close();


        *map = (new Map(width, height));


	return returnBool;
        // Implement code to read map data from file and construct the map
        // Example:
        // ifstream file(filename);
        // Read map data...
        // Modify map content based on the level (e.g., adjust characters and items)...
        // Construct map object...
    }

    Map *getMap() override
    {
        return map;
    }
};
/* 
int main()
{
    // Usage example:
    MapBuilder *mapSavedBuilder = new MapSavedBuilder();
    mapSavedBuilder->loadMap("mapInfo.txt");
    Map *savedMap = mapSavedBuilder->getMap();
    if (savedMap)
    {
        cout << savedMap->width << endl;
    }

    MapBuilder *mapGamePlayBuilder = new MapGamePlayBuilder();
    mapGamePlayBuilder->loadMap("mapInfoLevels.txt"); // Assuming level 5
    Map *adaptedMap = mapGamePlayBuilder->getMap();

    // Use the maps as needed...

    // Don't forget to delete the map objects and builders when done

    return 0;
} */
