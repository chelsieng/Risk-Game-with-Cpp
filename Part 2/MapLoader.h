#pragma once

#include <string>
#include <vector>
#include "../Part 1/Map.h"

class MapLoader {

private:
    string filePath;
    // Reading input file
    Map* resultMap;
    static Map* loadMap(const string& filePath); //helper method

public:
    MapLoader(); // Default Constructor
    explicit MapLoader(const string& filePath); //Constructor to read a domination file
    MapLoader(MapLoader &); //Copy constructor
    MapLoader &operator=(const MapLoader &); //Assignment operator

    ~MapLoader(); //Destructor
    // Parsing lines read from input file
    static std::vector<string> parseString(string s);
    // Map getter
    Map* getMap();
    //File Name getter
    string getMapName();
    // insertion stream operator
    friend ostream &operator<<(ostream &, const MapLoader &);
};
