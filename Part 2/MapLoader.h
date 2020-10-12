#pragma once

#include <string>
#include <vector>
#include "../Part 1/Map.h"

class MapLoader {

private:
    string fileName;
    static Map* validMap;
//    std::vector<std::vector<std::string>> countries;
//    std::vector<std::vector<std::string>> continents;

//    void copy(const MapLoader &); //Copying value of mapLoader


public:
    MapLoader(); // Default Constructor
    MapLoader(string fileName); //Constructor to read a domination file
    MapLoader(MapLoader &); //Copy constructor
    MapLoader &operator=(const MapLoader &); //Assignment operator
    ~MapLoader(); //Destructor

    // Reading input file
    static void loadMap(string fileName);

    friend ostream &operator<<(ostream &, const MapLoader &); // insertion stream operator
};
