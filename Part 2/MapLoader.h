//
//  MapLoader.h
//  A1
//
//  Created by Raffi Alan Bezirjian on 2020-09-26.
//  Copyright © 2020 Raffi Alan Bezirjian. All rights reserved.
//

#pragma once
#ifndef MapLoader_h
#define MapLoader_h

#include <iostream>
#include <regex>
#include <fstream>
#include "Map.h"

// This class is used for instantiating a map object after reading the map file
class MapLoader{
public:
    MapLoader();    //Constructor
    ~MapLoader();   //Destructor
    Map* ProduceMap(std::string filePath);
    
private:
    struct Data_True{   //Defining structure
        // Member Declarations
        bool bordersFound = false;
        bool fileFound = false;
        bool continentsFound = false;
        bool territoriesFound = false;
        bool trueData = true;
        
        inline bool validTrue(){
            return bordersFound && fileFound && continentsFound && territoriesFound && trueData;
        }
        
        
    };
    
    enum Data{Continents=0, Territories,Borders,None};
    
    Map* producedMap;
    std::vector<Continent*> continents;
    int numberOfContinents;
    int i;
    int* sizeOfContinents;
    int numberOfTerritories;
    int* sizeOfNeighbors;
    Data_True* data_true;
    std::vector<std::string> Split(std::string line) const;
    
    // Determining amount of continents
    void num_processContinents(std::string line, DataType* datatype);
    // Determining amount of territories
    void num_processTerritories(std::string line, DataType* datatype);
    // Determining amount of borders
    void num_processBorders(std::string line, DataType* datatype);
    // generating continents
    void generate_Continents(std::string line, DataType* datatype);
    // generating territories
    void generate_Territories(std::string line, DataType* datatype);
    // generating borders
    void generate_Borders(std::string line, DataType* datatype);
    // reading the file
    void fileReading(std::string path);
    
    
    
}


#endif /* MapLoader_h */
