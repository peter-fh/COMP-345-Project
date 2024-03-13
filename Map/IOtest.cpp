#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//-----TEST---------//
class Table
{
public:
    string woodType;
    int width;

public:
    // Default constructor
    Table() : woodType(""), width(0) {}

    // Constructor with parameters
    Table(const string &wood, int w) : woodType(wood), width(w) {}

    // Accessor functions
    string getWoodType() const
    {
        return woodType;
    }

    int getWidth() const
    {
        return width;
    }

    // toString function to represent the object as a string
    string toString() const
    {
        return "Wood Type: " + woodType + ", Width: " + to_string(width);
    }
};
//-----TEST---------//

class TableBuilder
{
public:
    virtual void loadTable(const std::string &filename) = 0;
    virtual Table *getTable() = 0;
};

// Concrete builder for reading the map as saved
class TableSavedBuilder : public TableBuilder
{
private:
    Table *table;

public:
    TableSavedBuilder() : table(nullptr) {}

    void loadTable(const std::string &filename) override
    {
        ifstream inputFile(filename);

        // Check if the file is opened successfully
        if (!inputFile.is_open())
        {
            cerr << "Error opening the file." << endl;
            return;
        }

        // Read attributes from the file
        string woodType;
        int width;
        inputFile >> woodType >> width;

        // Close the file
        inputFile.close();

        table = new Table(woodType, width);
    }

    Table *getTable() override
    {
        return table;
    }

    ~TableSavedBuilder()
    {
        delete table;
    }
};

int main()
{
    TableBuilder *tableSavedBuilder = new TableSavedBuilder();
    tableSavedBuilder->loadTable("tableInfo.txt");
    Table *savedTable = tableSavedBuilder->getTable();
    cout << savedTable->getWoodType() << endl;

    delete tableSavedBuilder;
    return 0;
}

// Table table1("Chene", 15);

// // Open the file for reading
// ifstream inputFile("table_attributes.txt");

// // Check if the file is opened successfully
// if (!inputFile.is_open())
// {
//     cerr << "Error opening the file." << endl;
//     return 1;
// }

// // Read attributes from the file
// string woodType;
// int width;
// inputFile >> woodType >> width;

// // Close the file
// inputFile.close();

// Table table1(woodType, width);

// std::cout << table1.toString() << std::endl;
// return 0;
