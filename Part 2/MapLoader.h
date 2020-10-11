//
// Created by Raffi Alan Bezirjian on 2020-10-01.
//

#pragma once
#include "Map.h"
#include <string>


class MapLoader {

private:
    string* fileName;
    Map* resultMap;

public:
    MapLoader();                                        //Default constructor
    MapLoader(MapLoader& map);                          //Copy constructor
    MapLoader& operator = (const MapLoader& map);       //Assignment operator
    ~MapLoader();                                       //Destructor

    MapLoader(string fileName);
    void ReadMap(string fileName);
    Map* GetMap(std::string filePath);

    vector<string> SplitWords(string s);
};
