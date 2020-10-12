#include "MapLoader.h"

// Constructor that reads a domination map file to create map object
MapLoader::MapLoader(string fileName) {

}

void MapLoader::copy(const MapLoader &mapLoader) {
    fileName = new string(*mapLoader.fileName);
}

MapLoader::MapLoader(MapLoader &mapLoader) {
    fileName = new string(*mapLoader.fileName);
} //Copy Constructor

MapLoader &MapLoader::operator=(const MapLoader &mapLoader) {
    //handling self assignment
    if (this != &mapLoader) {
        if (fileName != nullptr) {
            delete fileName; //Handling memory
        }
        if (resultMap != nullptr) {
            delete mapLoader.resultMap;
        }
        copy(mapLoader);
    }
    return *this;
} // End of assignment operator

MapLoader::~MapLoader() {
    delete fileName;
    delete resultMap;
} //End of destructor

ostream &operator<<(ostream &output, const MapLoader &mapLoader) {
    return output;
}

Map *MapLoader::GetMap(std::string filePath) {
    return nullptr;
}




