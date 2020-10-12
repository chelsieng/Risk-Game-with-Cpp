#pragma once
#ifndef A1_MAPLOADER_H
#define A1_MAPLOADER_H

#include <string>
#include "../Part 1/Map.h"

class MapLoader {

private:
    string *fileName;
    Map *resultMap;

    void copy(const MapLoader &); //Copying value of mapLoader
public:
    MapLoader(string fileName); //Constructor to read a domination file
    MapLoader(MapLoader &); //Copy constructor
    MapLoader &operator=(const MapLoader &); //Assignment operator
    ~MapLoader(); //Destructor
    friend ostream &operator<<(ostream &, const MapLoader &); // insertion stream operator

    Map *GetMap(std::string filePath);

//    vector<string> SplitWords(string s);
};


#endif //A1_MAPLOADER_H
