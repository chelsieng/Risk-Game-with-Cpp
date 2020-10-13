#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "MapLoader.h"

using namespace std;

// Default constructor
MapLoader::MapLoader() : fileName{""}
{}

// Parametrized constructor
MapLoader::MapLoader(string fileName) {
    this->fileName = fileName;
}

//void MapLoader::copy(const MapLoader &mapLoader) {
//    fileName = mapLoader.fileName;
//}

//Copy Constructor
MapLoader::MapLoader(MapLoader &mapLoader) {
    fileName = mapLoader.fileName;
}

// Assignment Operator Overload
MapLoader &MapLoader::operator=(const MapLoader &mapLoader) {
    //handling self assignment
    if (this != &mapLoader) {
        this->fileName = mapLoader.fileName;
    }
    return *this;
}

// Destructor
MapLoader::~MapLoader() {
    fileName = nullptr;
}

ostream &operator<<(ostream &output, const MapLoader &mapLoader) {
    return output;
}

//Map *MapLoader::GetMap(std::string filePath) {
//    return nullptr;
//}

// Reading the input file and generating a valid map
void MapLoader::loadMap(string fileName) {
    string line;
    ifstream inFile(fileName);

    std::ifstream input(fileName);
    while (!input.eof()) {
        string temp;
        getline(input, temp, '\n');
        std::cout << temp << "\n";
    }
}







