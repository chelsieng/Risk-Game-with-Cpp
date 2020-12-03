#pragma once

#include <string>
#include <vector>
#include "Map.h"

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
    virtual Map* getMap();
    //File Name getter
    virtual string getMapName();
    // insertion stream operator
    friend ostream &operator<<(ostream &, const MapLoader &);
};

// adaptee
class ConquestFileReader {
private:
    string filePath;
    // Reading input file
    Map* resultMap;
    static Map* loadMap(const string& filePath); //helper method

public:
    ConquestFileReader(); // Default Constructor
    explicit ConquestFileReader(const string& filePath); //Constructor to read a domination file
    ConquestFileReader(ConquestFileReader &); //Copy constructor
    ConquestFileReader &operator=(const ConquestFileReader &); //Assignment operator

    ~ConquestFileReader(); //Destructor
    // Parsing lines read from input file
    static std::vector<string> parseString(string s);
    // Map getter
    Map* getMap();
    //File Name getter
    string getMapName();
    // insertion stream operator
    friend ostream &operator<<(ostream &, const ConquestFileReader &);

};

// adapter interface
class ConquestFileReaderAdapter : public MapLoader {
private:
    ConquestFileReader* conquestFileReader_;
public:
    explicit ConquestFileReaderAdapter(ConquestFileReader* conquestFileReader) : conquestFileReader_(conquestFileReader){};
    ConquestFileReaderAdapter(ConquestFileReaderAdapter &); //Copy constructor
    ConquestFileReaderAdapter &operator=(const ConquestFileReaderAdapter &); //Assignment operator
    ~ConquestFileReaderAdapter();

    Map* getMap() override {return this->conquestFileReader_->getMap();}

    friend ostream &operator<<(ostream &, const ConquestFileReader &);
};

// Simulate client side code
Map* generateMap(MapLoader* mapLoader);